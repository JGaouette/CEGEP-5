package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"time"
)

func main() {
	c := make(chan string)

	for i := 0; i < 10; i++ {
		go primeNumber(i, c)
	}

	go printer(c)

	var input string
	fmt.Scanln(&input)
}

func printer(c chan string) {
	for {
		msg := <-c
		fmt.Println(msg)
		time.Sleep(time.Second * 1)
	}
}

func primeNumber(n int, c chan string) {
	rand.Seed(time.Now().UnixNano())

	var isPrime bool = false
	var nb int

	for !isPrime {
		nb = rand.Intn(9999) + 1

		i := nb - 1

		for i > 1 {
			if nb%i == 0 {
				break
			}
			i--
		}

		if i == 1 {
			isPrime = true
			c <- strconv.Itoa(n) + " : " + strconv.Itoa(nb)
		}
	}
}

/* Solution A
func main() {
	for i := 0; i < 10; i++ {
		go primeNumber(i)
	}
	var input string
	fmt.Scanln(&input)
}

func primeNumber(n int) {
	rand.Seed(time.Now().UnixNano())

	var isPrime bool = false
	var nb int

	for !isPrime {
		nb = rand.Intn(9999) + 1

		i := nb - 1

		for i > 1 {
			if nb%i == 0 {
				break
			}
			i--
		}

		if i == 1 {
			isPrime = true
			fmt.Printf("%v : %v \n", n, nb)
		}
	}
}
*/
