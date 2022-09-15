package main

import (
	"fmt"
	calcul "module/math"
)

func main() {
	fmt.Println("Starting")
	calcul.Somme([]float64{1})

}

func FibR(n int) int {
	if n < 2 {
		return n
	}
	return FibR(n-1) + FibR(n-2)
}

func FibT(n int) int {
	return innerFibT(n, 0, 1)
}

func innerFibT(n, first, second int) int {
	if n == 0 {
		return first
	}
	return innerFibT(n-1, second, first+second)
}
