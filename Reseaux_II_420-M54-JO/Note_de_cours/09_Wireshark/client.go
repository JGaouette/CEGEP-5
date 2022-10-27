package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"time"
)

func main() {
	conn, err := net.Dial("tcp", ":8000")
	if err != nil {
		log.Fatalln(err)
	}
	defer conn.Close()

	for {
		msg, err := bufio.NewReader(conn).ReadString('\n')
		if err != nil {
			log.Fatalln(err)
		}

		fmt.Print("->: ", msg)
		time.Sleep(time.Second)
	}
}
