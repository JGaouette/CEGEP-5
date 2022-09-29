package main

import (
	"flag"
	"io"
	"log"
	"net/http"
	"os"
	"strings"
)

func main() {
	if !techExists("admin") {
		createTech("admin", "admin", true)
	}

	//Init server
	var addr = flag.String("addr", ":8080", "http service address")
	flag.Parse()
	hub := newHub()
	go hub.run()
	http.HandleFunc("/", loadHome)
	http.HandleFunc("/ws", func(w http.ResponseWriter, r *http.Request) { serveWs(hub, w, r) })

	http.HandleFunc("/client", loadClient)
	http.HandleFunc("/tech", loadTech)
	http.HandleFunc("/404", load404)
	//http.HandleFunc("/home", loadHome)

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
	log.Println(r.URL)
	if r.URL.Path != "/" {
		http.Error(w, "Not found", http.StatusNotFound)
		return
	}
	/*
		if r.Method != http.MethodGet {
			http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
			return
		}
	*/
	switch r.Method {
	case "GET":

	case "POST":
		r.ParseForm()
		username := r.Form.Get("username")
		password := r.Form.Get("password")

		log.Println(techLogin(username, password))
	}
	
	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Home", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Clavardage du C.A.I", 1)

	content, _ := os.ReadFile("./www/views/home/home.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))

	//http.ServeFile(w, r, "./www/views/home/home.html")

}

func loadClient(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Client", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Client", 1)

	content, _ := os.ReadFile("./www/views/home/client.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
}

func loadTech(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Tech", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Tech", 1)

	content, _ := os.ReadFile("./www/views/home/tech.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
}

func load404(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - 404", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "404", 1)

	content, _ := os.ReadFile("./www/views/home/404.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
}
