package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
)

func main() {
	conn, err := net.Dial("tcp", ":8000")
	if err != nil {
		log.Fatalln(err)
	}
	defer conn.Close()

	for {
		var msg string
		fmt.Scanln(&msg)

		_, err = io.WriteString(conn, msg+"\n")
		if err != nil {
			log.Fatalln(err)
		}
		fmt.Println("Send: ", msg)

		msg, err = bufio.NewReader(conn).ReadString('\n')
		if err != nil {
			log.Fatalln(err)
		}
		fmt.Println("Receive: ", msg)
	}
}
