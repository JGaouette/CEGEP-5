package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	c "utils/const"
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

	var i uint32
	for i = 0; i < uint32(len(payload)); i += 32 {
		var end = i + 32
		if end > uint32(len(payload)) {
			end = uint32(len(payload))
		}

		//Envoie le type du message
		binary.Write(conn, binary.BigEndian, c.TYPE_STRING)

		//Envoie la taille du message
		binary.Write(conn, binary.BigEndian, end-i)

		//Envoie le message
		conn.Write([]byte(payload[i:end]))
	}

	var payload2 = []byte{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	var i2 uint32
	for i2 = 0; i2 < uint32(len(payload2)); i2 += 32 {
		var end = i2 + 32
		if end > uint32(len(payload2)) {
			end = uint32(len(payload2))
		}

		//Envoie le type du message
		binary.Write(conn, binary.BigEndian, c.TYPE_BINARY)

		//Envoie la taille du message
		binary.Write(conn, binary.BigEndian, end-i2)

		//Envoie le message
		conn.Write(payload2[i2:end])
	}

	var payload3 = 7846

	//Envoie le type du message
	binary.Write(conn, binary.BigEndian, c.TYPE_INT)

	//Envoie la taille du message
	binary.Write(conn, binary.BigEndian, 4)

	//Envoie le message
	binary.Write(conn, binary.BigEndian, payload3)
}
