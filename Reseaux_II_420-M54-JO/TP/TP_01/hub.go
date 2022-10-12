package main

import (
	"encoding/json"
	"log"
)

type Hub struct {
	broadcast chan []byte

	tech       *User
	techLogin  chan *User
	techLogout chan *User

	clients      map[string]*User
	clientLogin  chan *User
	clientLogout chan *User
}

func newHub() *Hub {
	return &Hub{
		broadcast: make(chan []byte),

		tech:       nil,
		techLogin:  make(chan *User),
		techLogout: make(chan *User),

		clientLogin:  make(chan *User),
		clientLogout: make(chan *User),
		clients:      make(map[string]*User),
	}
}

func (h *Hub) run() {
	for {
		select {
		case pong := <-h.broadcast:
			log.Println("Broadcasting message: ", string(pong))

			var message map[string]string
			err := json.Unmarshal(pong, &message)
			if err != nil {
				return
			}

			if message["clientID"] != "" {
				client := h.clients[message["clientID"]]
				if h.tech == nil {
					return
				}
				select {
				case h.tech.send <- pong:
					log.Println("Client -> Tech :", message["msg"])
				default:
					delete(h.clients, message["clientID"])
					close(client.send)
				}
			} else {
				client := h.clients[message["techID"]]
				if client != nil {
					select {
					case client.send <- pong:
						log.Println("Tech -> Client :", message["msg"])
					default:
						delete(h.clients, message["techID"])
						close(client.send)
					}
				}
			}
		case user := <-h.techLogin:
			log.Println("Tech is connecting")
			h.tech = user

		case <-h.techLogout:
			log.Println("Tech is disconnecting")
			h.tech = nil

			//close all clients
			for id := range h.clients {
				close(h.clients[id].send)
				delete(h.clients, id)
			}

		case user := <-h.clientLogin:
			log.Println("Client is connecting")
			id := user.conn.RemoteAddr().String()

			h.clients[id] = user

			toSend, _ := json.Marshal(map[string]string{"type": "Login", "id": id})
			if h.tech != nil {
				select {
				case h.tech.send <- toSend:
				default:
					close(h.tech.send)
				}
			}
			h.clients[id].send <- toSend

		case user := <-h.clientLogout:
			log.Println("Client is disconnecting")
			id := user.conn.RemoteAddr().String()

			if _, ok := h.clients[id]; ok {
				toSend, _ := json.Marshal(map[string]string{"type": "Logout", "id": id})
				h.tech.send <- toSend

				delete(h.clients, id)
				close(user.send)
			}
		}
	}
}
