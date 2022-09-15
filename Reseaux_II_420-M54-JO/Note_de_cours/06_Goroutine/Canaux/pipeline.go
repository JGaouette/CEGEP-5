package main

import (
	"fmt"
)

func _main() {
	nombres := make(chan int)
	carres := make(chan int)

	go Compteur(nombres)
	//go Carre(carres, nombres)

	go func(out chan<- int, in <-chan int) {
		for x := range in {
			out <- x * x
		}

		defer close(out)
	}(carres, nombres)

	for x := range carres {
		fmt.Println(x)
	}
}

func Compteur(out chan<- int) {
	for x := 0; x < 100; x++ {
		out <- x
	}

	defer close(out)
}

/*

func Carre(out chan<- int, in <-chan int) {
	for x := range in {
		out <- x * x
	}

	defer close(out)
}
*/
