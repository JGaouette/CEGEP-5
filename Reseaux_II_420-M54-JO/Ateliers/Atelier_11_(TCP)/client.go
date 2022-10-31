package main

import (
	"encoding/binary"
	"fmt"
	"log"
	"net"
)

func main() {
	conn, err := net.DialTCP("tcp", nil, &net.TCPAddr{Port: 8000})
	if err != nil {
		log.Fatal(err.Error())
	}

	var t uint8  //Type du message
	var l uint32 //Taille du message
	binary.Read(conn, binary.BigEndian, &t)
	//if t == 1 {
	binary.Read(conn, binary.BigEndian, &l)
	var v = make([]byte, l) //Valeur du message
	conn.Read(v)
	fmt.Println(string(v))
	//}
}
