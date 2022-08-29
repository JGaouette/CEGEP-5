package main

import (
	"fmt"
	strings "strings"
)

func ____main() {
	tel := "4/50s?&9;``<^)6g0h315d"

	fmt.Println(tel)

	for i := 0; i <= 255; i++ {
		tel = strings.ReplaceAll(tel, string(rune(i)), "")

		if i == 47 {
			i = 58
		}
	}
}
