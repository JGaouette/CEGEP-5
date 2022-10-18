/*
Créez un serveur Web Go. Votre serveur doit gérer une page web et un websocket. La page doit afficher un champ numérique et un bouton. Lorsque l'utilisateur clique sur le bouton, la valeur dans le champ est envoyé via websocket à Go, le serveur double le nombre et le retourne, on affiche la valeur doublée dans le champ numérique.

Considérez que l'utilisateur va entrer des informations valides.

Sur votre serveur, vous devez avoir une goroutine qui sert juste à faire le calcul, votre goroutine de websocket ne doit pas faire d'opération mathématique!
*/

package main

import (
	"flag"
	"github.com/gorilla/websocket"
	"io"
	"log"
	"net/http"
	"os"
	"strconv"
)

func main() {
	chanResult := make(chan int)
	defer close(chanResult)

	//Init server
	var addr = flag.String("addr", ":8080", "http service address")
	flag.Parse()
	http.HandleFunc("/", loadHome)
	http.HandleFunc("/ws", func(w http.ResponseWriter, r *http.Request) {
		wsHandler(w, r, chanResult)
	})

	//File server
	fileServer := http.FileServer(http.Dir("./www/assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fileServer))

	//Start server
	err := http.ListenAndServe(*addr, nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}

func loadHome(w http.ResponseWriter, r *http.Request) {
	content, _ := os.ReadFile("./www/views/index.html")
	contentView := string(content)
	io.WriteString(w, contentView)
}

func wsHandler(w http.ResponseWriter, r *http.Request, c chan int) {
	upgrader := websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println(err)
	}

	go doubleNumber(c)

	for {
		_, msg, err := conn.ReadMessage()
		if err != nil {
			log.Println(err)
		}
		log.Println(string(msg))
		n, _ := strconv.Atoi(string(msg))

		c <- n

		conn.WriteMessage(1, []byte(strconv.Itoa(<-c)))
	}
}

func doubleNumber(c chan int) {

	select {
	case n := <-c:
		c <- n * 2
	}

}
