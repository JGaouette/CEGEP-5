package main

import (
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

/*
func clientWebsocket(w http.ResponseWriter, r *http.Request, c chan string) {
	var upgrader = websocket.Upgrader{} // use default options
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer conn.Close()

	go writer(conn, c)
	go reader(conn, c)
}
*/

func clientWs(w http.ResponseWriter, r *http.Request, techChan chan string, clientChan chan string) {
	var upgrader = websocket.Upgrader{} // use default options
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	//defer conn.Close()

	go writer(conn, techChan)
	go reader(conn, clientChan)
}

func techWs(w http.ResponseWriter, r *http.Request, techChan chan string, clientChan chan string) {
	var upgrader = websocket.Upgrader{} // use default options
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	//defer conn.Close()

	go writer(conn, clientChan)
	go reader(conn, techChan)
}

func reader(conn *websocket.Conn, c chan string) {
	for {
		_, message, err := conn.ReadMessage()
		if err != nil {
			log.Println("read:", err)
			return
		}
		c <- string(message)
	}
}

func writer(conn *websocket.Conn, c chan string) {
	for {
		message := <-c
		err := conn.WriteMessage(websocket.TextMessage, []byte(message))
		if err != nil {
			log.Println("write:", err)
			return
		}
	}
}
