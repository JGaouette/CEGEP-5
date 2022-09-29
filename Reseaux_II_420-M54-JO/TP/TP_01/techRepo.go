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
	_, err := statement.Exec(username, any(hashPassword(password)), admin)
	if err != nil {
		log.Fatal(err)
		return false
	}
	return true
}

func techLogin(username string, password string) bool {
	var passwordEncrypted string

	err := getDatabase().QueryRow("SELECT tech_password FROM Techs WHERE tech_username = ?;", username).Scan(&passwordEncrypted)

	if err != nil {
		return false
	}

	if !checkPasswordHash(password, passwordEncrypted) {
		return false
	}
	return true
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

func hashPassword(password string) string {
	bytes, _ := bcrypt.GenerateFromPassword([]byte(password), 14)
	return string(bytes)
}

func checkPasswordHash(password, hash string) bool {
	err := bcrypt.CompareHashAndPassword([]byte(hash), []byte(password))
	return err == nil
}
