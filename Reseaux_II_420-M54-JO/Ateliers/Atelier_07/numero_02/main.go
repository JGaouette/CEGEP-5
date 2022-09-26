package main

import (
	"github.com/gorilla/websocket"
	"io"
	"log"
	"net/http"
	"os"
	"strconv"
)

var upgrader = websocket.Upgrader{}

func main() {
	http.HandleFunc("/", loadIndex)
	http.HandleFunc("/ws", ws)

	fileServer := http.FileServer(http.Dir("./www/assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fileServer))

	//Goroutine de w
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Println("ListendAndServe:", err)
		return
	}
}

func loadIndex(w http.ResponseWriter, _ *http.Request) {
	vueRaw, _ := os.ReadFile("./www/views/index.html")
	vue := string(vueRaw)
	io.WriteString(w, vue)
}

func ws(w http.ResponseWriter, r *http.Request) {
	c, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		return
	}

	defer func(c *websocket.Conn) {
		err := c.Close()
		if err != nil {
			log.Println("Close:", err)
		}
	}(c)

	for {
		total := 0
		msgType, message, err := c.ReadMessage()
		if err != nil {
			log.Println("read:", err)
			break

		}

		if msgType == websocket.CloseMessage {
			log.Println("Fermeture du socket")
			break
		}

		number, _ := strconv.Atoi(string(message))
		total += number

		c.WriteMessage(msgType, []byte(strconv.Itoa(total)))

		/*
			log.Printf("recv: %s", message)
			err = c.WriteMessage(mt, message)
			if err != nil {
				log.Println("write:", err)
				break
			}
		*/
	}
}
