package main

import (
	"fmt"
	"math/rand"
)

func main() {
	cache := make(map[int]int)

	for i := 0; i <= 100; i++ {
		rand := rand.Intn(200)
		cache[rand] = syracuse(rand)
	}

	fmt.Println(cache)
}

func syracuse(x int) int {
	count := 1

	for x != 1 {
		if x%2 == 0 {
			count += 1
			x /= 2
		} else {
			count += 1
			x = (x * 3) + 1
		}
	}

	return count
}
