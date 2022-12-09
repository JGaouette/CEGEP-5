package main

import (
	"encoding/json"
	"github.com/gorilla/mux"
	_ "github.com/gorilla/mux"
	"net/http"
	"strconv"
)

type DogFact struct {
	Facts   string `json:"facts"`
	Success bool   `json:"success"`
}

var facts = []DogFact{
	{Facts: "Dogo"},
	{Facts: "Barf"},
}

func main() {
	routeur := mux.NewRouter()
	routeur.HandleFunc("/facts", returnAll).Methods(http.MethodGet)
	routeur.HandleFunc("/facts/id}", returnOne).Methods(http.MethodGet)
	routeur.HandleFunc("/facts", create).Methods(http.MethodPost)
	routeur.HandleFunc("/facts/{id}", update).Methods(http.MethodPut)
	routeur.HandleFunc("/facts/{id}", delete).Methods(http.MethodDelete)
	http.ListenAndServe(":8080", routeur)
}

func returnAll(w http.ResponseWriter, r *http.Request) {

	json.NewEncoder(w).Encode(facts)
}

func returnOne(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, _ := strconv.Atoi(vars["id"])
	json.NewEncoder(w).Encode(facts[id])
}

func delete(writer http.ResponseWriter, request *http.Request) {

}

func update(writer http.ResponseWriter, request *http.Request) {

}

func create(writer http.ResponseWriter, request *http.Request) {

}
