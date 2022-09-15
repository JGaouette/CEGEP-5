package main

import (
	"fmt"
	"time"
)

func ___main() {
	maxGoroutines := 10
	guard := make(chan struct{}, maxGoroutines)

	for i := 0; i < 30; i++ {
		guard <- struct{}{} // bloque lorsqu'on arrive à maxGoroutines
		go func(n int) {
			worker(n)
			<-guard
		}(i)
	}
}

func worker(i int) {
	fmt.Println("travaille sur la tâche ", i)
	time.Sleep(5 * time.Second)
}
