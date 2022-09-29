package main

import (
	"database/sql"
	_ "github.com/mattn/go-sqlite3"
	"golang.org/x/crypto/bcrypt"
	"log"
)

func getDatabase() *sql.DB {
	database, err := sql.Open("sqlite3", "./db/technicians.db")
	if err != nil {
		log.Fatal(err)
	}
	return database
}

func createTech(username string, password string, isAdmin bool) bool {
	if techExists(username) {
		return false
	}

	admin := 0
	if isAdmin {
		admin = 1
	}

	statement, _ := getDatabase().Prepare("INSERT INTO Techs (tech_username, tech_password, tech_admin) VALUES (?, ?, ?)")
	_, err := statement.Exec(username, any(hash(password)), admin)
	if err != nil {
		log.Fatal(err)
		return false
	}
	return true
}

func createToken(username string) string {
	token := hash(username)

	statement, _ := getDatabase().Prepare("UPDATE Techs SET tech_token = ? WHERE tech_username = ?")
	_, err := statement.Exec(token, username)
	if err != nil {
		log.Fatal(err)
		return ""
	}
	return token
}

func techLogin(username string, password string) int {
	var passwordEncrypted string

	err := getDatabase().QueryRow("SELECT tech_password FROM Techs WHERE tech_username = ?;", username).Scan(&passwordEncrypted)
	if err != nil {
		log.Println(err)
		return 0
	}

	if !checkHash(password, passwordEncrypted) {
		return 0
	}

	var isAdmin int
	getDatabase().QueryRow("SELECT tech_admin FROM Techs WHERE tech_username = ?;", username).Scan(&isAdmin)
	if isAdmin == 0 {
		return 1
	}
	return 2
}

func techExists(username string) bool {
	var exists int

	err := getDatabase().QueryRow("SELECT COUNT(tech_id) FROM Techs WHERE tech_username = ?;", username).Scan(&exists)
	if err != nil {
		log.Print(err)
	}

	if exists == 0 {
		return false
	}
	return true
}

func isConnectedAndAdmin(token string) (bool, bool) {
	var isAdmin int

	err := getDatabase().QueryRow("SELECT tech_admin FROM Techs WHERE tech_token = ?;", token).Scan(&isAdmin)
	if err != nil {
		log.Println(err)
		return false, false
	}

	if isAdmin == 0 {
		return true, false
	}
	return true, true
}

func hash(password string) string {
	bytes, _ := bcrypt.GenerateFromPassword([]byte(password), 14)
	return string(bytes)
}

func checkHash(password, hash string) bool {
	err := bcrypt.CompareHashAndPassword([]byte(hash), []byte(password))
	return err == nil
}
