package main

import (
	"fmt"
	"time"
)

func __main() {
	var c chan string = make(chan string)
	go pinger(c)
	go printer(c)
	time.Sleep(time.Millisecond * 500)
	go ponger(c)
	var input string
	fmt.Scanln(&input)
}

func pinger(c chan<- string) {
	for i := 0; ; i++ {
		c <- "ping"
	}
}

func ponger(c chan<- string) {
	for i := 0; ; i++ {
		c <- "pong"
		time.Sleep(time.Second * 1)
	}
}

func printer(c <-chan string) {
	for {
		msg := <-c
		fmt.Println(msg)
		time.Sleep(time.Second * 1)
	}
}
