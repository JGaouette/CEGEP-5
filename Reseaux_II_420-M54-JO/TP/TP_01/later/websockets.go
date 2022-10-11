package later

import (
	"encoding/json"
	"github.com/gorilla/websocket"
	"log"
	"net/http"
	"tp_01"
)

func techWs(w http.ResponseWriter, r *http.Request, chanTechs map[int]chan main.Message, chanClient chan main.Message) {
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

	id := len(chanTechs) + 1
	chanTechs[id] = make(chan main.Message)

	go write(conn, chanTechs[id], chanClose)

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

func clientWs(w http.ResponseWriter, r *http.Request, chanTechs map[int]chan main.Message, chanClient chan main.Message) {
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
	go write(conn, chanClient, chanClose)
	for {
		select {
		case msg := <-chanTechs[1]:
			log.Println("Message received by tech: ", msg)
			err := conn.WriteJSON(msg)
			if err != nil {
				log.Println("WriteJSON() error: ", err)
				break
			}

		case <-chanClose:
			log.Println("User disconnected")
			return
		}
	}
}

func write(conn *websocket.Conn, c chan main.Message, chanClose chan bool) {
	var message main.Message
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
