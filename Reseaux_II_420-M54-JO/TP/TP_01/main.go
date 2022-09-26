package main

import (
	"flag"
	"log"
	"net/http"
	"os"
)

var addr = flag.String("addr", ":8085", "http service address")

func main() {
	//Init server
	flag.Parse()
	hub := newHub()
	go hub.run()
	http.HandleFunc("/", loadIndex)
	http.HandleFunc("/ws", func(w http.ResponseWriter, r *http.Request) {
		serveWs(hub, w, r)
	})
	http.HandleFunc("/tech/create", func(w http.ResponseWriter, r *http.Request) {
		os.ReadFile("./www/views/tech/create.php")
	})
	http.HandleFunc("/tech/", func(w http.ResponseWriter, r *http.Request) {
		os.ReadFile("./www/views/tech/read.php")
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

func loadIndex(w http.ResponseWriter, r *http.Request) {
	log.Println(r.URL)
	if r.URL.Path != "/" {
		http.Error(w, "Not found", http.StatusNotFound)
		return
	}
	if r.Method != http.MethodGet {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}
	http.ServeFile(w, r, "./www/views/home/index.html")
}
