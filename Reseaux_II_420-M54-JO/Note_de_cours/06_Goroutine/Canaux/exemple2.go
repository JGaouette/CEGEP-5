package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	fmt.Println("Compte à rebours")
	abort := make(chan struct{})
	go func() {
		os.Stdin.Read(make([]byte, 1)) // read a single byte
		abort <- struct{}{}
	}()

	tick := time.NewTicker(1 * time.Second)

	for countdown := 10; countdown > 0; countdown-- {
		fmt.Printf("%v...", countdown)
		select {

		case <-tick.C: // Ne fait rien
		case <-abort:
			fmt.Println("Décollage annulé!")
			return // quitte la fonction main
		}
	}
	launch()
}

func launch() {
	fmt.Println("Décollage")
}
