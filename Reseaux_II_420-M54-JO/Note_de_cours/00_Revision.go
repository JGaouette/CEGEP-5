/*
!- Type de variable -!
int, int8, int16, int32, int64
uint, uiny8, uint16, uint32, uint64
complex64, complex128
float32, float64

!- Facon écrire variable -!
var nombre int = 10
var nombre = 10
nombre := 10

!- Tableau et slice -!
t := [3]int{1, 2, 3}  -> [1 2 3] //Tableau
t := []int{1, 2, 3}  -> [1 2 3]  //slice
s := t[1:3]           -> [2 3]   //slice
s := t[1:]                       //Juste : = jusqu'à la fin

s = append(t, 9)

!- If -!
if calcul := 8 % 2; calcul == 0 {
	fmt.Println("ok")
}

if 8%2 == 0{
	fmt.Println("ok")
}
*/

package main

import (
	"fmt"
	"time"
)

func _main() {
	//Switch case
	time := time.Now()
	switch {
	case time.Hour() < 12:
		fmt.Println("Avant-midi")
	default:
		fmt.Println("Après-midi")
	}

	//For
	for i := 0; i < 10; i++ {
		fmt.Println(i)
	}

	//While
	j := 0
	for j < 10 {
		fmt.Println(j)
		j++
	}

	//For each (i = indice, v = value)
	t := []string{"patate", "carotte", "Michel"}
	for i, v := range t {
		fmt.Println(i)
		fmt.Println(v)
	}

	// Function
	a := add(3, 4)
	a, b := addAndMultiply(3, 4)
	fmt.Println(a)
	fmt.Println(b)

	//Fonction inline (Mettre fonction dans variable)
	inc := func(no int) int {
		return no + 1
	}
	x := 5
	x = inc(x)
	fmt.Println(x)
}

// Function
func add(x int, y int) int {
	return x + y
}

// Function with undefined args number
func addMore(args ...int) int {
	sum := 0
	for _, v := range args {
		sum += v
	}
	return sum
}

// Function that return multiple values
func addAndMultiply(x int, y int) (int, int) {
	defer fmt.Println("fini") //? S'active à la fin
	return x + y, x * y
}

// Recursive function
func fact(x uint) uint {
	if x == 0 {
		return 1
	}
	return x * fact(x-1)
}

// Tail recursive (60% better function)
func factTR(n uint, a uint) uint {
	if n == 0 {
		return a
	}

	return factTR(n-1, n*a)
}

func fact2(x uint) uint {
	return factTR(x, 1)
}
