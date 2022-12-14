package main

import (
	"flag"
	"github.com/gorilla/websocket"
	"io"
	"log"
	"math/rand"
	"net/http"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	if !techExists("admin") {
		createTech("admin", "admin", true)
	}
	if !techExists("tech") {
		createTech("tech", "tech", false)
	}

	hub := newHub()
	go hub.run()

	//Init server
	var addr = flag.String("addr", ":8080", "http service address")
	flag.Parse()
	http.HandleFunc("/", loadHome)
	http.HandleFunc("/ws", func(w http.ResponseWriter, r *http.Request) {
		userWs(w, r, hub)
	})

	http.HandleFunc("/client", loadClient)
	http.HandleFunc("/tech", loadTech)
	http.HandleFunc("/404", load404)

	http.HandleFunc("/admin", loadAdmin)
	http.HandleFunc("/admin/create", loadCreate)
	http.HandleFunc("/admin/edit", loadEdit)
	http.HandleFunc("/admin/delete", loadDelete)

	http.HandleFunc("/logout", loadLogout)

	//File server
	fileServer := http.FileServer(http.Dir("./www/assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fileServer))

	//Start server
	err := http.ListenAndServe(*addr, nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}

func userWs(w http.ResponseWriter, r *http.Request, hub *Hub) {
	upgrader := websocket.Upgrader{}
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		return
	}

	user := &User{hub: hub, conn: conn, send: make(chan []byte, 256)}

	cookie, err := r.Cookie("techToken")
	if err != nil {
		cookie = &http.Cookie{}
	}

	if isConnected(cookie.Value) {
		user.hub.techLogin <- user
	} else {
		user.hub.clientLogin <- user
	}

	go user.write()
	go user.read()
}

func loadHome(w http.ResponseWriter, r *http.Request) {
	redirectTech(w, r)

	now := time.Now()

	if r.URL.Path != "/" {
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	w.Header().Set("Content-Type", "text/html")

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = headerDisconnect(r, headerView)

	switch r.Method {
	case "GET":
		headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
		headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)
	case "POST":
		r.ParseForm()
		username := r.Form.Get("username")
		password := r.Form.Get("password")

		if techLogin(username, password, now.Format("2006-01-02 15:04:05")) == 0 {
			headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
			headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Information de connection invalide, veuillez r??essayer.", 1)
		} else {
			token := hash(username + strconv.Itoa(rand.Intn(100)))
			var sessionCookie http.Cookie

			if techLogin(username, password, now.Format("2006-01-02 15:04:05")) == 1 {
				if someoneIsConnected() {
					headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
					headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Un technicien est d??j?? connect??, veuillez r??essayer plus tard", 1)
				} else {
					sessionCookie = http.Cookie{Name: "adminToken", Value: "", HttpOnly: true, MaxAge: -1}
					http.SetCookie(w, &sessionCookie)

					sessionCookie = http.Cookie{Name: "techToken", Value: token, HttpOnly: true}
					http.SetCookie(w, &sessionCookie)
					http.Redirect(w, r, "/tech", http.StatusTemporaryRedirect)

					updateToken(username, token)
					return
				}
			} else {
				sessionCookie = http.Cookie{Name: "techToken", Value: "", HttpOnly: true, MaxAge: -1}
				http.SetCookie(w, &sessionCookie)

				sessionCookie = http.Cookie{Name: "adminToken", Value: token, HttpOnly: true}
				http.SetCookie(w, &sessionCookie)
				http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
				return
			}
		}
		log.Println("Login: ", techLogin(username, password, now.Format("2006-01-02 15:04:05")))
	}

	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Home", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Clavardage du C.A.I", 1)

	content, _ := os.ReadFile("./www/views/home/home.html")
	contentView := string(content)

	cookie, _ := r.Cookie("techToken")

	var cookieValue string

	if cookie != nil {
		cookieValue = cookie.Value
	} else {
		cookieValue = "FALSE"
	}

	if isConnected(cookieValue) {
		contentView = strings.Replace(contentView, "{{YOU-ARE-CONNECTED-VISIBILITY}}", "inline", 1)
		contentView = strings.Replace(contentView, "{{YOU-ARE--NOT-CONNECTED-VISIBILITY}}", "none", 1)
		//TODO: Disable these 2 lines
		contentView = strings.Replace(contentView, "{{ONLINE-VISIBILITY}}", "inline", 1)
		contentView = strings.Replace(contentView, "{{OFFLINE-VISIBILITY}}", "none", 1)
	} else if someoneIsConnected() {
		contentView = strings.Replace(contentView, "{{YOU-ARE-CONNECTED-VISIBILITY}}", "none", 1)
		contentView = strings.Replace(contentView, "{{YOU-ARE--NOT-CONNECTED-VISIBILITY}}", "inline", 1)
		contentView = strings.Replace(contentView, "{{ONLINE-VISIBILITY}}", "inline", 1)
		contentView = strings.Replace(contentView, "{{OFFLINE-VISIBILITY}}", "none", 1)
	} else {
		contentView = strings.Replace(contentView, "{{YOU-ARE-CONNECTED-VISIBILITY}}", "none", 1)
		contentView = strings.Replace(contentView, "{{YOU-ARE--NOT-CONNECTED-VISIBILITY}}", "inline", 1)
		contentView = strings.Replace(contentView, "{{ONLINE-VISIBILITY}}", "none", 1)
		contentView = strings.Replace(contentView, "{{OFFLINE-VISIBILITY}}", "inline", 1)
	}

	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+contentView+string(footer))

	//http.ServeFile(w, r, "./www/views/home/home.html")
}

func loadAdmin(w http.ResponseWriter, r *http.Request) {
	redirect(w, r, true)

	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = headerDisconnect(r, headerView)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Admin", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Admin", 1)
	headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
	headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "block", 1)
	headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)

	content, _ := os.ReadFile("./www/views/admin/admin.html")
	contentView := string(content)

	techIds := getAllTechIds()

	tech := ""
	allTechView := ""
	techItem, _ := os.ReadFile("./www/views/templates/techItem.html")

	for _, techId := range techIds {
		tech = getTechUsername(techId)
		techItemView := string(techItem)
		login, logout := getTechHistoric(techId)
		techItemView = strings.Replace(techItemView, "{{TECH_ID}}", strconv.Itoa(techId), 2)
		techItemView = strings.Replace(techItemView, "{{TECH_USERNAME}}", tech, 1)
		techItemView = strings.Replace(techItemView, "{{TECH_LOGIN_TIME}}", login, 1)
		techItemView = strings.Replace(techItemView, "{{TECH_LOGOUT_TIME}}", logout, 1)
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
	headerView = headerDisconnect(r, headerView)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Create", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Create", 1)
	headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "block", 1)

	switch r.Method {
	case "GET":
		headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
		headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)
	case "POST":
		r.ParseForm()
		username := r.Form.Get("username")
		password1 := r.Form.Get("password1")
		password2 := r.Form.Get("password2")

		if username == "" || password1 == "" || password2 == "" {
			headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
			headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Veuillez remplir tous les champs.", 1)

		} else {
			if password1 != password2 {
				headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
				headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Les mots de passes ne sont pas identique, veuillez r??essayer", 1)
			} else {
				if techExists(username) {
					headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
					headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Ce technicien exist d??j??, veuillez r??essayer", 1)
				} else {
					createTech(username, password1, false)
					http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
					return
				}
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
	headerView = headerDisconnect(r, headerView)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Edit", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Edit", 1)
	headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "block", 1)
	content, _ := os.ReadFile("./www/views/admin/edit.html")
	contentView := string(content)

	techId := 0
	queryId := r.URL.Query().Get("techId")

	if queryId == "" {
		log.Println("Trying to edit tech without providing ID")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	techId, _ = strconv.Atoi(queryId)
	techUsername := getTechUsername(techId)

	if techId == 1 {
		log.Println("You do not have the permission to edit this user")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	if techUsername == "" || techId == 0 {
		log.Println("No user with this id exists")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	switch r.Method {
	case "GET":
		headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
		headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)

	case "POST":
		r.ParseForm()
		username := r.Form.Get("username")
		password1 := r.Form.Get("password1")
		password2 := r.Form.Get("password2")

		if username == "" || password1 == "" || password2 == "" {
			headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
			headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Veuillez remplir tous les champs.", 1)
		} else {
			if password1 != password2 {
				headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
				headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Les mots de passes ne sont pas identique, veuillez r??essayer", 1)
			} else {
				if username != techUsername && techExists(username) {
					headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "inline", 1)
					headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "Ce technicien exist d??j??, veuillez r??essayer", 1)
				} else {
					updateTech(techId, username, password1)
					http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
					return
				}
			}
		}
	}

	contentView = strings.Replace(contentView, "{{TECH_USERNAME}}", techUsername, 1)

	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+contentView+string(footer))
}

func loadDelete(w http.ResponseWriter, r *http.Request) {
	redirect(w, r, true)

	queryId := r.URL.Query().Get("techId")

	if queryId == "" {
		log.Println("Trying to delete tech without providing ID")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	techId, _ := strconv.Atoi(queryId)
	techUsername := getTechUsername(techId)

	if techId == 1 {
		log.Println("You do not have the permission to delete this user")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	if techUsername == "" {
		log.Println("No user with this id exists")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	deleteTech(techId)

	http.Redirect(w, r, "/admin", http.StatusTemporaryRedirect)
}

func loadTech(w http.ResponseWriter, r *http.Request) {
	redirect(w, r, false)

	w.Header().Set("Content-Type", "text/html")

	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = headerDisconnect(r, headerView)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - Tech", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "Tech", 1)
	headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
	headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)
	headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "block", 1)

	content, _ := os.ReadFile("./www/views/home/tech.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
}

func loadClient(w http.ResponseWriter, r *http.Request) {
	redirectTech(w, r)

	if !someoneIsConnected() {
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
		return
	}

	w.Header().Set("Content-Type", "text/html")
	log.Println(r.URL)

	header, _ := os.ReadFile("./www/views/templates/header.html")
	headerView := string(header)
	headerView = strings.Replace(headerView, "{{TITLE}}", "TP1 - User", 1)
	headerView = strings.Replace(headerView, "{{H1}}", "User", 1)
	headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "none", 1)
	headerView = strings.Replace(headerView, "{{ERROR_VISIBILITY}}", "none", 1)
	headerView = strings.Replace(headerView, "{{ERROR_TEXT}}", "", 1)

	content, _ := os.ReadFile("./www/views/home/client.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
}

func loadLogout(w http.ResponseWriter, r *http.Request) {
	var cookie *http.Cookie
	var err error
	now := time.Now()

	cookie, err = r.Cookie("adminToken")
	if err == nil {
		sessionCookie := http.Cookie{Name: "adminToken", Value: "", HttpOnly: true, MaxAge: -1}
		http.SetCookie(w, &sessionCookie)
		http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
	}

	cookie, err = r.Cookie("techToken")
	if err != nil {
		log.Println("No need to logout")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	queryId := r.URL.Query().Get("userId")

	if queryId == "" {
		log.Println("No id provided")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	userId, _ := strconv.Atoi(queryId)
	username := getTechUsername(userId)

	if username == "" {
		log.Println("No user with this id exists")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	userToken := getToken(userId)

	if userToken != cookie.Value {
		log.Println("Invalid token")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	logoutUser(userId, now.Format("2006-01-02 15:04:05"))
	sessionCookie := http.Cookie{Name: "techToken", Value: "", HttpOnly: true, MaxAge: -1}
	http.SetCookie(w, &sessionCookie)

	http.Redirect(w, r, "/", http.StatusTemporaryRedirect)
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
	headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "none", 1)

	content, _ := os.ReadFile("./www/views/home/404.html")
	footer, _ := os.ReadFile("./www/views/templates/footer.html")

	io.WriteString(w, headerView+string(content)+string(footer))
}

func redirect(w http.ResponseWriter, r *http.Request, needAdmin bool) {
	var cookie *http.Cookie
	var err error

	if needAdmin {
		cookie, err = r.Cookie("adminToken")
		if err != nil {
			log.Println("No cookie found")
			http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
			return
		}
		return
	}

	cookie, err = r.Cookie("techToken")

	if err != nil {
		log.Println("No cookie found")
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}

	isConnected := isConnected(cookie.Value)

	if !isConnected {
		http.Redirect(w, r, "/404", http.StatusTemporaryRedirect)
		return
	}
}

func redirectTech(w http.ResponseWriter, r *http.Request) {
	cookie, err := r.Cookie("techToken")

	if err != nil {
		return
	}

	if isConnected(cookie.Value) {
		http.Redirect(w, r, "/tech", http.StatusTemporaryRedirect)
		return
	}
}

func headerDisconnect(r *http.Request, headerView string) string {
	var cookie *http.Cookie
	var err error
	id := 0

	cookie, err = r.Cookie("adminToken")
	if err == nil {
		headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "block", 1)
		headerView = strings.Replace(headerView, "{{LOGOUT_ID}}", "1", 1)

		return headerView
	}

	cookie, err = r.Cookie("techToken")
	if err == nil {
		id = getUserByToken(cookie.Value)
		headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "block", 1)
		headerView = strings.Replace(headerView, "{{LOGOUT_ID}}", strconv.Itoa(id), 1)

		return headerView
	}

	headerView = strings.Replace(headerView, "{{LOGOUT_VISIBILITY}}", "none", 1)
	headerView = strings.Replace(headerView, "{{LOGOUT_}}", "0", 1)

	return headerView
}
