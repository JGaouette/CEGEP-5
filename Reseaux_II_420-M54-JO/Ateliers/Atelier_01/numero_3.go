package main

import (
	"fmt"
)

func main() {
	x := []int{48, 96, 86, 68, 57, 82, 63, 70, 37, 34, 83, 27, 19, 97, 9, 17}

	min, max, moy := minmaxmoy(x)

	fmt.Printf("min: %v, max: %v, moy: %v\n", min, max, moy)
}

func minmaxmoy(x []int) (int, int, int) {
	min := int(x[0])
	max := int(x[0])
	moy := 0

	for i := 0; i < len(x); i++ {
		if min > x[i] {
			min = x[i]
		}

		if max < x[i] {
			max = x[i]
		}

		moy += x[i]
	}

	moy = moy / len(x)
	return min, max, moy
}
