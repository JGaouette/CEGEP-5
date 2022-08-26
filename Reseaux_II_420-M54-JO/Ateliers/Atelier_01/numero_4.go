package main

import (
	"fmt"
	"strconv"
)

func main() {
	fmt.Printf(strconv.Itoa(syracuse(1)))
}

func syracuse(x int) int {
	count := 1

	for x != 1 {
		if x%2 == 0 {
			count += 1
			x = x / 2
		} else {
			count += 1
			x = (x * 3) + 1
		}
	}

	return count
}
