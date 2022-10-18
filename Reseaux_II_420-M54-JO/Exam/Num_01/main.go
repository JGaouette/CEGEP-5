package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	var c = make(chan string)
	defer close(c)

	go pinger(c)
	go printer(c)
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
	}
}

func printer(c <-chan string) {
	rand.Seed(time.Now().UTC().UnixNano())
	score := [2]int{0, 0}
	for {
		msg := <-c

		time.Sleep(time.Millisecond * 1000)

		if msg == "ping" {
			n := rand.Intn(99)
			if n < 10 {
				score[0]++
				fmt.Println("Point pour ping, score ", score[0], "-", score[1])
			}
		} else if msg == "pong" {
			n := rand.Intn(99)
			if n < 10 {
				score[1]++
				fmt.Println("Point pour pong, score ", score[0], "-", score[1])
			}
		} else {
			fmt.Println(msg)
		}
	}
}
