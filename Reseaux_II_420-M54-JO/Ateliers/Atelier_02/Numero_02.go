package main

import (
	"fmt"
)

//var cache map[int]int = make(map[int]int)

func main() {
	cache := make(map[int]int)

	for i := 0; i <= 100; i++ {
		rand := i
		cache[rand] = syracuse(rand)
	}

	fmt.Println(cache)
}

func syracuse(x int) int {
	count := 1

	for x != 1 {
		if x%2 == 0 {
			x /= 2
		} else {
			x = (x * 3) + 1
		}
		count += 1
	}

	return count
}
