package main

import (
	"encoding/json"
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

func techWs(w http.ResponseWriter, r *http.Request, chanTech chan<- Message, chanClient <-chan Message) {
	var upgrader = websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer conn.Close()

	w.Header().Add("Content-Type", "text/json")

	var chanClose = make(chan bool)
	defer close(chanClose)

	log.Println("Connect to WebSocket: ", r.RemoteAddr)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	go write(conn, chanTech, chanClose)
	for {
		select {
		case msg := <-chanClient:
			log.Println("Message received by client: ", msg)
			err := conn.WriteJSON(msg)
			if err != nil {
				log.Println("WriteJSON() error: ", err)
				break
			}

		case <-chanClose:
			log.Println("Tech disconnected")
			return
		}
	}
}

func clientWs(w http.ResponseWriter, r *http.Request, chanTech <-chan Message, chanClient chan<- Message) {
	var upgrader = websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer conn.Close()

	w.Header().Add("Content-Type", "text/json")

	var chanClose chan bool = make(chan bool)
	defer close(chanClose)

	log.Println("Connect to WebSocket: ", r.RemoteAddr)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	go write(conn, chanClient, chanClose)
	for {
		select {
		case msg := <-chanTech:
			log.Println("Message received by tech: ", msg)
			err := conn.WriteJSON(msg)
			if err != nil {
				log.Println("WriteJSON() error: ", err)
				break
			}

		case <-chanClose:
			log.Println("Client disconnected")
			return
		}
	}
}

func write(conn *websocket.Conn, c chan<- Message, chanClose chan<- bool) {
	var message Message
	defer func() { chanClose <- true }()
	for {
		msgType, msg, err := conn.ReadMessage()
		if err != nil {
			log.Println("ReadMessage() error: ", err)
			break
		}

		if msgType == -1 || msgType == websocket.CloseMessage {
			log.Println("Connection closed")
			break
		}

		err = json.Unmarshal(msg, &message)
		if err != nil {
			log.Println("Unmarhal() error: ", err)
			break
		}

		if msgType == websocket.TextMessage {
			log.Println("Sending: ", message)
			c <- message
		}
	}
}
