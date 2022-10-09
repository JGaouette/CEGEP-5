package main

import (
	"database/sql"
	_ "github.com/mattn/go-sqlite3"
	"log"
)

var database *sql.DB

func getDatabase() *sql.DB {
	if database == nil {
		var err error
		database, err = sql.Open("sqlite3", "./db/technicians.db")
		if err != nil {
			log.Fatal(err)
		}
	}
	return database
}

func getAllTechIds() []int {
	rows, err := getDatabase().Query("SELECT tech_id FROM Techs WHERE tech_admin = 0;")
	if err != nil {
		log.Fatal(err)
	}

	var ids []int
	for rows.Next() {
		var id int
		err = rows.Scan(&id)
		if err != nil {
			log.Fatal(err)
		}
		ids = append(ids, id)
	}
	return ids
}

func getTechUsername(id int) string {
	var username string

	err := getDatabase().QueryRow("SELECT tech_username FROM Techs WHERE tech_id = ?;", id).Scan(&username)
	if err != nil {
		log.Println(err)
		return ""
	}

	return username
}

func updateTech(id int, username string, password string) bool {
	statement, _ := getDatabase().Prepare("UPDATE Techs SET tech_username = ?, tech_password = ? WHERE tech_id = ?")
	_, err := statement.Exec(username, any(hash(password)), id)

	if err != nil {
		log.Fatal(err)
		return false
	}
	return true
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

func deleteTech(id int) bool {
	statement, _ := getDatabase().Prepare("DELETE FROM Techs WHERE tech_id = ?")
	_, err := statement.Exec(id)
	if err != nil {
		log.Fatal(err)
		return false
	}
	return true
}

func updateToken(username string, token string) bool {
	statement, _ := getDatabase().Prepare("UPDATE Techs SET tech_token = ? WHERE tech_username = ?")
	_, err := statement.Exec(token, username)
	if err != nil {
		log.Fatal(err)
		return false
	}
	return true
}

func getToken(id int) string {
	var token string

	err := getDatabase().QueryRow("SELECT tech_token FROM Techs WHERE tech_id = ?;", id).Scan(&token)
	if err != nil {
		log.Println(err)
		return ""
	}

	return token
}

func getUserByToken(token string) int {
	var id int

	err := getDatabase().QueryRow("SELECT tech_id FROM Techs WHERE tech_token = ?;", token).Scan(&id)
	if err != nil {
		log.Println(err)
		return 0
	}

	return id
}

func logoutUser(id int, logoutTime string) bool {
	statement, _ := getDatabase().Prepare("UPDATE Techs SET tech_token = NULL, tech_logout_time = ? WHERE tech_id = ?")
	_, err := statement.Exec(logoutTime, id)
	if err != nil {
		log.Fatal(err)
		return false
	}
	return true
}

func techLogin(username string, password string, loginTime string) int {
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
		statement, _ := getDatabase().Prepare("UPDATE Techs SET tech_login_time = ? WHERE tech_username = ?")
		_, err := statement.Exec(loginTime, username)
		if err != nil {
			log.Fatal(err)
			return 0
		}
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

func getTechHistoric(id int) (string, string) {
	var loginTime string
	var logoutTime string

	err := getDatabase().QueryRow("SELECT tech_login_time FROM Techs WHERE tech_id = ?;", id).Scan(&loginTime)
	if err != nil {
		loginTime = "N/A"
	}

	err = getDatabase().QueryRow("SELECT tech_logout_time FROM Techs WHERE tech_id = ?;", id).Scan(&logoutTime)
	if err != nil {
		logoutTime = "N/A"
	}

	return loginTime, logoutTime
}

func someoneIsConnected() bool {
	var id int

	err := getDatabase().QueryRow("SELECT tech_id FROM Techs WHERE tech_token <> '';").Scan(&id)
	if err != nil {
		return false
	}
	return true
}

func isConnected(token string) bool {
	var exists int

	err := getDatabase().QueryRow("SELECT COUNT(tech_id) FROM Techs WHERE tech_token = ?;", token).Scan(&exists)
	if err != nil {
		log.Print(err)
	}

	if exists == 0 {
		return false
	}
	return true
}
