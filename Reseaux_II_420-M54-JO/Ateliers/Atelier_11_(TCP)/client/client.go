package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
	c "utils/const"
)

func main() {
	conn, err := net.DialTCP("tcp", nil, &net.TCPAddr{Port: 8000})
	if err != nil {
		log.Fatal(err.Error())
	}

	var t uint8  //Type du message
	var l uint32 //Taille du message
	var v []byte //Valeur du message

	for {
		binary.Read(conn, binary.BigEndian, &t)
		binary.Read(conn, binary.BigEndian, &l)

		switch t {
		case c.TYPE_STRING:
			v = make([]byte, l)
			conn.Read(v)
			fmt.Println("string:", string(v))
			break

		case c.TYPE_BINARY:
			v = make([]byte, l)
			conn.Read(v)
			fmt.Println("binary:", v)
			break

		case c.TYPE_INT:
			binary.Read(conn, binary.BigEndian, &v)
			fmt.Println("integer:", v)
			break
		}
	}
}
