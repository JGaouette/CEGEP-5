package main

func ___main() {
	number := 7

	addMore(&number, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13)

	println(number)
}

func addMore(number *int, args ...int) {
	for _, v := range args {
		*number += v
	}
}
