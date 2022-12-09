package main

import (
	"bufio"
	"crypto/tls"
	"fmt"
	"io"
	"net"
	"time"
)

func main() {
	cert, err := tls.LoadX509KeyPair("../localhost/cert.pem", "../localhost/key.pem")
	if err != nil {
		fmt.Println(err)
		return
	}

	ssh := &tls.Config{Certificates: []tls.Certificate{cert}}
	server, _ := tls.Listen("tcp", "localhost:8001", ssh)

	go client()
	for {
		conn, _ := server.Accept()
		go func(conn net.Conn) {
			for {
				io.WriteString(conn, "Hello from TCP\n")
				time.Sleep(time.Second)
			}
		}(conn)
	}
}

func client() {
	ssh := tls.Config{InsecureSkipVerify: true}
	conn, err := tls.Dial("tcp", "localhost:8001", &ssh)
	if err != nil {
		fmt.Println(err)
	}
	for {
		message, _ := bufio.NewReader(conn).ReadString('\n')
		fmt.Println("Message Received:", string(message))
		time.Sleep(time.Second)
	}
}
