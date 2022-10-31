package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
)

const (
	TYPE_STRING uint8 = iota + 1
	TYPE_BINARY
	TYPE_INT
)

func main() {
	server, err := net.ListenTCP("tcp", &net.TCPAddr{Port: 8000})
	if err != nil {
		log.Fatalln(err)
	}
	defer func() {
		fmt.Println("Fermeture du serveur")
		server.Close()
	}()

	fmt.Println("Serveur démarré sur le port 8000")

	for {
		conn, _ := server.AcceptTCP()
		go manage(conn)
	}
}

func manage(conn *net.TCPConn) {
	//Envoie le type du message
	binary.Write(conn, binary.BigEndian, TYPE_STRING)

	//Le message
	var payload = []byte("Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum \n Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum \n Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum")

	//Envoie la taille du message
	binary.Write(conn, binary.BigEndian, uint32(len(payload)))

	//Envoie le message
	conn.Write(payload)
}
