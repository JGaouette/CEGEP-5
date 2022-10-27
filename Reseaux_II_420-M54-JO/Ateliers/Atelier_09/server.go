package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
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
		fmt.Println("Nouvelle connexion client")
		go handleConnexion(conn)
	}
}

func handleConnexion(c net.Conn) {
	defer func() {
		defer c.Close()
		fmt.Println("Fermeture de la connexion client")
	}()

	for {
		fmt.Println("Attente d'un message client")
		msg, err := bufio.NewReader(c).ReadString('\n')
		if err != nil {
			log.Println(err)
			break
		}
		fmt.Println("Receive: ", msg)

		_, err = io.WriteString(c, msg)
		if err != nil {
			log.Fatalln(err)
		}
		fmt.Println("Send: ", msg)
		
		/*
			_, err := io.WriteString(c, "\n")
			if err != nil {
				break
			}
			time.Sleep(time.Second)
		*/
	}
}
