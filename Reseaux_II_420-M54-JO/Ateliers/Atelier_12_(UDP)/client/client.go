package main

import (
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	udpServer, err := net.ResolveUDPAddr("udp", ":8000")

	if err != nil {
		log.Fatal(err)
	}
	conn, _ := net.DialUDP("udp", nil, udpServer)

	defer func() {
		fmt.Println("Fermeture du serveur")
		conn.Close()
	}()
	conn.Write([]byte("Client request connection"))

	for {
		buf := make([]byte, 1024)
		n, _, _ := conn.ReadFromUDP(buf)

		fmt.Println(string(buf[0:n]))
		conn.Read(buf)
		fmt.Println(string(buf))
		time.Sleep(time.Second)
	}
}
