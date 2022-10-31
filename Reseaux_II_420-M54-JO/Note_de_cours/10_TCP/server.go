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
	//Le message
	var payload = "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum \n Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum \n Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum"

	var payloadParts = make([][]byte, 0)
	for i := 0; i < len(payload); i += 32 {
		payloadParts = append(payloadParts, []byte(payload[i:i+32]))
	}

	for _, part := range payloadParts {
		//Envoie le type du message
		binary.Write(conn, binary.BigEndian, TYPE_STRING)
		//Envoie la taille du message
		binary.Write(conn, binary.BigEndian, uint32(len(part)))
		//Envoie le message
		conn.Write(part)
	}
}
