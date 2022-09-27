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
	http.HandleFunc("/result", loadResult)
	http.HandleFunc("/ws", ws)

	fileServer := http.FileServer(http.Dir("./www/assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fileServer))

	err := http.ListenAndServe(":8085", nil)
	if err != nil {
		log.Println("ListendAndServe:", err)
		return
	}
}

func loadIndex(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path != "/" {
		http.NotFound(w, r)
		return
	}

	switch r.Method {
	case "GET":
		w.Header().Set("Content-Type", "text/html")
		content, _ := os.ReadFile("./www/views/index.html")
		io.WriteString(w, string(content))
	case "POST":
		no1, _ := strconv.Atoi(r.FormValue("no1"))
		no2, _ := strconv.Atoi(r.FormValue("no2"))
		var result = no1 + no2
		var resultCookie = http.Cookie{Name: "result", Value: strconv.Itoa(result)}
		http.SetCookie(w, &resultCookie)
		http.Redirect(w, r, "/result", http.StatusTemporaryRedirect)
	}
	/*

		vueRaw, _ := os.ReadFile("./www/views/index.html")
		vue := string(vueRaw)
		vue = strings.Replace(vue, "{{name}}", "John", 1)
		w.Header().Set("Content-Type", "text/html")
		io.WriteString(w, vue)
	*/
}

func loadResult(w http.ResponseWriter, _ *http.Request) {
	vueRaw, _ := os.ReadFile("./www/views/result.html")
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
		mt, message, err := c.ReadMessage()
		if err != nil {
			log.Println("read:", err)
			break

		}
		log.Printf("recv: %s", message)
		err = c.WriteMessage(mt, message)
		if err != nil {
			log.Println("write:", err)
			break
		}
	}
}
