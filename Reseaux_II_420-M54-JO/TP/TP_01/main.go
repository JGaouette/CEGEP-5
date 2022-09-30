package main

import (
	"flag"
	"io"
	"log"
	"net/http"
	"os"
	"strconv"
	"strings"
)

func main() {
	if !techExists("admin") {
		createTech("admin", "admin", true)
	}
	if !techExists("tech") {
		createTech("tech", "tech", false)
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

	http.HandleFunc("/admin", loadAdmin)
	http.HandleFunc("/admin/create", loadCreate)
	http.HandleFunc("/admin/edit", loadEdit)

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

	w.Header().Set("Content-Type", "text/html")

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)

	switch r.Method {
	case "GET":
		headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
		headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)
	case "POST":
		r.ParseForm()
		username := r.Form.Get("username")
		password := r.Form.Get("password")

		if techLogin(username, password) == 0 {
			headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
			headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Information de connection invalide, veuillez réessayer.", 1)
		} else {
			token := createToken(username)
			var sessionCookie = http.Cookie{Name: "token", Value: token, HttpOnly: true}
			http.SetCookie(w, &sessionCookie)

			if techLogin(username, password) == 1 {
				http.Redirect(w, r, "/tech", http.StatusTemporaryRedirect)
				return
			} else {
				http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
				return
			}
		}

		log.Println(techLogin(username, password))
	}

	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Home", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Clavardage du C.A.I", 1)

	content, _ := os.ReadFile("./www/views/home/home.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))

	//http.ServeFile(w, r, "./www/views/home/home.html")

}

func loadAdmin(w http.ResponseWriter, r *http.Request) {
	redirect(w, r, true)

	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Admin", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Admin", 1)
	headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
	headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)

	content, _ := os.ReadFile("./www/views/admin/admin.html")
	contentView := string(content)

	techIds := getAllTechIds()

	//get all techs and add them to the table
	tech := ""
	allTechView := ""
	for _, techId := range techIds {
		tech = getTechUsername(techId)
		techItem, _ := os.ReadFile("./www/views/templates/techItem.html")
		techItemView := string(techItem)
		techItemView = strings.Replace(techItemView, "{{TECH_ID}}", strconv.Itoa(techId), 1)
		techItemView = strings.Replace(techItemView, "{{TECH_USERNAME}}", tech, 1)
		allTechView += techItemView
	}

	contentView = strings.Replace(contentView, "{{TECHS}}", allTechView, 1)

	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+contentView+string(footer))
}

func loadCreate(w http.ResponseWriter, r *http.Request) {
	redirect(w, r, true)

	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Create", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Create", 1)

	switch r.Method {
	case "GET":
		headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
		headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)
	case "POST":
		r.ParseForm()
		username := r.Form.Get("username")
		password1 := r.Form.Get("password1")
		password2 := r.Form.Get("password2")

		if password1 != password2 {
			headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
			headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Les mots de passes ne sont pas identique, veuillez réessayer", 1)
		} else {
			if techExists(username) {
				headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
				headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Ce technicien exist déjà, veuillez réessayer", 1)
			} else {
				createTech(username, password1, false)
				http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
				return
			}
		}
	}

	content, _ := os.ReadFile("./www/views/admin/create.html")
	contentView := string(content)

	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+contentView+string(footer))
}

func loadEdit(w http.ResponseWriter, r *http.Request) {
	redirect(w, r, true)

	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Edit", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Edit", 1)
	content, _ := os.ReadFile("./www/views/admin/edit.html")
	contentView := string(content)

	techId := 0
	techUsername := ""

	switch r.Method {
	case "GET":
		headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
		headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)

		queryId := r.URL.Query().Get("techId")
		techId, _ = strconv.Atoi(queryId)
		techUsername = getTechUsername(techId)
		contentView = strings.Replace(contentView, "{{TECH_USERNAME}}", techUsername, 1)

	case "POST":
		r.ParseForm()
		username := r.Form.Get("username")
		password1 := r.Form.Get("password1")
		password2 := r.Form.Get("password2")

		if password1 != password2 {
			headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
			headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Les mots de passes ne sont pas identique, veuillez réessayer", 1)
		} else {
			if username != techUsername && techExists(username) {
				headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
				headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Ce technicien exist déjà, veuillez réessayer", 1)
			} else {
				updateTech(techId, username, password1)
				http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
				return
			}
		}
	}

	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+contentView+string(footer))
}

func loadTech(w http.ResponseWriter, r *http.Request) {
	redirect(w, r, false)

	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Tech", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Tech", 1)
	headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
	headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Information de connection invalide, veuillez réessayer.", 1)

	content, _ := os.ReadFile("./www/views/home/tech.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
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

func load404(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - 404", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "404", 1)
	headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
	headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)

	content, _ := os.ReadFile("./www/views/home/404.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
}

func redirect(w http.ResponseWriter, r *http.Request, needAdmin bool) {
	cookie, _ := r.Cookie("token")
	isConnected, isAdmin := isConnectedAndAdmin(cookie.Value)

	if !isConnected {
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	if needAdmin && !isAdmin {
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}
}
