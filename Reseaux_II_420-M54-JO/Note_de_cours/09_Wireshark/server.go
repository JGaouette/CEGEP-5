package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"time"
)

func main() {
	server, err := net.Listen("tcp", ":8000")
	if err != nil {
		log.Fatalln(err)
	}
	defer func() {
		fmt.Println("Fermeture du serveur")
		server.Close()
	}()

	fmt.Println("Serveur démarré sur le port 8000")

	for {
		conn, err := server.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go handleConnexion(conn)
	}
}

func handleConnexion(c net.Conn) {
	defer c.Close()
	for {
		_, err := io.WriteString(c, time.Now().Format("15:04:05\n"))
		if err != nil {
			break
		}
		time.Sleep(time.Second)
	}
}
