package main

import (
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	server, err := net.ListenUDP("udp", &net.UDPAddr{Port: 8000})
	if err != nil {
		log.Fatalln(err)
	}

	defer func() {
		fmt.Println("Fermeture du serveur")
		server.Close()
	}()

	buf := make([]byte, 1024)

	for {
		_, clientAddr, _ := server.ReadFromUDP(buf)
		fmt.Println("Client connected from", clientAddr)
		go manageClient(server, clientAddr)
	}
}

func manageClient(server *net.UDPConn, clientAddr *net.UDPAddr) {
	for {
		now := []byte(time.Now().Format(time.ANSIC))
		server.WriteToUDP(now, clientAddr)
		time.Sleep(time.Second)
	}
}
