package main

import (
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

func techWs(w http.ResponseWriter, r *http.Request, chanTech chan<- string, chanClient <-chan string) {
	var upgrader = websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer conn.Close()

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
			conn.WriteMessage(websocket.TextMessage, []byte(msg))

		case <-chanClose:
			log.Println("Tech disconnected")
			return
		}
	}
}

func clientWs(w http.ResponseWriter, r *http.Request, chanTech <-chan string, chanClient chan<- string) {
	var upgrader = websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer conn.Close()

	var chanClose chan bool = make(chan bool)
	defer close(chanClose)

	log.Println("Connection au WebSocket; ", r.RemoteAddr)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	go write(conn, chanClient, chanClose)
	for {
		select {
		case msg := <-chanTech:
			log.Println("Message received by tech: ", msg)
			conn.WriteMessage(websocket.TextMessage, []byte(msg))

		case <-chanClose:
			log.Println("Client disconnected")
			return
		}
	}
}

func write(conn *websocket.Conn, c chan<- string, chanClose chan<- bool) {
	defer func() { chanClose <- true }()
	for {
		msgType, msg, err := conn.ReadMessage()

		if err != nil {
			log.Println(err)
			break
		}
		if msgType == -1 || msgType == websocket.CloseMessage {
			log.Println("Connection closed")
			break
		}

		if msgType == websocket.TextMessage {
			conn.WriteMessage(websocket.TextMessage, msg)
			c <- string(msg)
			log.Println("Sending: ", string(msg))
		}
	}
}

/*
func clientWs(w http.ResponseWriter, r *http.Request, techChan chan string, clientChan chan string) {
	var chanClose = make(chan bool)
	defer close(chanClose)

	var upgrader = websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer conn.Close()

	go writer(conn, techChan, chanClose)

	for {
		msgType, message, err := conn.ReadMessage()
		log.Println("penis")
		if err != nil {
			log.Println("Error Read:", err)
			return
		}

		if msgType == websocket.TextMessage {
			log.Println("Text Read:", message)
			clientChan <- string(message)
		}

		if msgType == websocket.CloseMessage {
			log.Println("Close Read")
			chanClose <- true
			return
		}
	}
}

func techWs(w http.ResponseWriter, r *http.Request, techChan chan string, clientChan chan string) {
	var chanClose = make(chan bool)
	defer close(chanClose)

	var upgrader = websocket.Upgrader{} // use default options
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer conn.Close()

	go writer(conn, clientChan, chanClose)

	for {
		log.Println("UwU2")
		msgType, message, err := conn.ReadMessage()
		log.Println("penis")
		if err != nil {
			log.Println("Error Read:", err)
			return
		}

		if msgType == websocket.TextMessage {
			log.Println("Text Read:", message)
			techChan <- string(message)
		}

		if msgType == websocket.CloseMessage {
			log.Println("Close Read")
			chanClose <- true
			return
		}
	}
}

func writer(conn *websocket.Conn, c chan string, chanClose chan bool) {
	for {
		log.Println("UwU")
		select {
		case msg := <-c:
			err := conn.WriteMessage(websocket.TextMessage, []byte(msg))
			if err != nil {
				log.Println("Error Write:", err)
			}
			log.Println("Message Write:", msg)
		case <-chanClose:
			close(c)
			return
		}
	}
}
*/
