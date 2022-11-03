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
	conn, err := net.DialTCP("tcp", nil, &net.TCPAddr{Port: 8000})
	if err != nil {
		log.Fatal(err.Error())
	}

	var t uint8  //Type du message
	var l uint32 //Taille du message

	for {
		binary.Read(conn, binary.BigEndian, &t)

		if t == TYPE_STRING {
			binary.Read(conn, binary.BigEndian, &l)
			var v = make([]byte, l) //Valeur du message
			conn.Read(v)
			fmt.Println(string(v))
		}
	}
}
