// Copyright 2013 The Gorilla WebSocket Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"bytes"
	"net/http"
	"time"

	"github.com/gorilla/websocket"
)

const (
	writeWait      = 10 * time.Second
	pongWait       = 60 * time.Second
	pingPeriod     = (pongWait * 9) / 10
	maxMessageSize = 512
)

var (
	newline = []byte{'\n'}
	space   = []byte{' '}
)

type User struct {
	hub  *Hub
	conn *websocket.Conn
	send chan []byte
}

func userWs(w http.ResponseWriter, r *http.Request, hub *Hub) {
	upgrader := websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		return
	}

	user := &User{hub: hub, conn: conn, send: make(chan []byte, 256)}

	cookie, err := r.Cookie("techToken")
	if err != nil {
		cookie = &http.Cookie{}
	}

	if isConnected(cookie.Value) {
		user.hub.techLogin <- user
	} else {
		user.hub.clientLogin <- user
	}

	go user.write()
	go user.read()
}

func (c *User) read() {
	defer func() {
		if c.hub.tech == c {
			c.hub.techLogout <- c
		} else {
			c.hub.clientLogout <- c
		}

		c.conn.Close()
	}()

	c.conn.SetReadLimit(maxMessageSize)
	c.conn.SetReadDeadline(time.Now().Add(pongWait))
	c.conn.SetPongHandler(func(string) error { c.conn.SetReadDeadline(time.Now().Add(pongWait)); return nil })

	for {
		_, message, err := c.conn.ReadMessage()
		if err != nil {
			return
		}

		message = bytes.TrimSpace(bytes.Replace(message, newline, space, -1))
		c.hub.broadcast <- message
	}
}

func (c *User) write() {
	ticker := time.NewTicker(pingPeriod)
	defer func() {
		ticker.Stop()
		c.conn.Close()
	}()
	for {
		select {
		case message, ok := <-c.send:
			if !ok {
				err := c.conn.WriteMessage(websocket.CloseMessage, []byte{})
				if err != nil {
					return
				}
				return
			}

			w, err := c.conn.NextWriter(websocket.TextMessage)
			if err != nil {
				return
			}

			_, err = w.Write(message)
			if err != nil {
				return
			}

			n := len(c.send)
			for i := 0; i < n; i++ {
				_, err := w.Write(<-c.send)
				if err != nil {
					return
				}
			}

			if err := w.Close(); err != nil {
				return
			}
		case <-ticker.C:
			if err := c.conn.WriteMessage(websocket.PingMessage, nil); err != nil {
				return
			}
		}
	}
}
