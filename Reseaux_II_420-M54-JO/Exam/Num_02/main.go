package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	chan1 := make(chan int, 5)
	defer close(chan1)
	chan2 := make(chan int, 5)
	defer close(chan2)
	chan3 := make(chan int, 5)
	defer close(chan3)
	chan4 := make(chan int, 5)
	defer close(chan4)
	chan5 := make(chan int, 5)
	defer close(chan5)
	chan6 := make(chan int, 5)
	defer close(chan6)

	rand.Seed(time.Now().UTC().UnixNano())

	go fct1(chan1, chan2)
	go fct2(chan2, chan3)
	go fct3(chan3, chan4)
	go fct4(chan4, chan5)
	go fct5(chan5, chan6)
	go fct6(chan6)

	for i := 0; i < 100; i++ {
		chan1 <- rand.Intn(100)
	}

	var input string
	fmt.Scanln(&input)
}

func fct1(c <-chan int, c2 chan<- int) {
	for {
		nb := <-c
		c2 <- nb * 2
	}
}

func fct2(c <-chan int, c2 chan<- int) {
	for {
		nb := <-c
		c2 <- nb / 3
	}
}

func fct3(c <-chan int, c2 chan<- int) {
	for {
		nb := <-c
		c2 <- nb - 10
	}
}

func fct4(c <-chan int, c2 chan<- int) {
	for {
		nb := <-c

		if nb < 0 {
			c2 <- 0
		} else {
			c2 <- nb
		}
	}
}

func fct5(c <-chan int, c2 chan<- int) {
	for {
		nb := <-c
		c2 <- nb + 1
	}
}

func fct6(c <-chan int) {
	for {
		msg := <-c
		fmt.Println(msg)
	}
}
