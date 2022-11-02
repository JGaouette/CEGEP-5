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
	var payload = "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum \n Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum \n Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum"

	//send payload in parts of 32 bytes
	var i uint32
	for i = 0; i < uint32(len(payload)); i += 32 {
		var end = i + 32
		if end > uint32(len(payload)) {
			end = uint32(len(payload))
		}
		binary.Write(conn, binary.BigEndian, end-i)
		conn.Write([]byte(payload[i:end]))
	}
}
