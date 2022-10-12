package main

import (
	"github.com/gorilla/websocket"
)

type User struct {
	hub  *Hub
	conn *websocket.Conn
	send chan []byte
}

func (c *User) read() {
	defer func() {
		if c.hub.tech == c {
			c.hub.techLogout <- c
		} else {
			c.hub.clientLogout <- c
		}

		err := c.conn.Close()
		if err != nil {
			return
		}
	}()

	for {
		_, message, err := c.conn.ReadMessage()
		if err != nil {
			return
		}

		c.hub.broadcast <- message
	}
}

func (c *User) write() {
	defer func() {
		err := c.conn.Close()
		if err != nil {
			return
		}
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
		}
	}
}
