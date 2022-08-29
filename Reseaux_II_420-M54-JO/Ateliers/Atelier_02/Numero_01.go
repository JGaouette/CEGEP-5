package main

import (
	"fmt"
	strings "strings"
)

func _main() {
	var s string = "La patate douce n’est pas apparentée à la pomme de terre, malgré son nom. Elle est dotée d'une très grande richesse en pro-vitamine A (ou bêta-carotène). Elle fournit aussi une énergie de longue durée, grâce à l’amidon qu’elle renferme."

	s = strings.ToLower(s)
	s = strings.ReplaceAll(s, "’", " ")
	s = strings.ReplaceAll(s, "'", " ")
	s = strings.ReplaceAll(s, "(", "")
	s = strings.ReplaceAll(s, ")", "")
	s = strings.ReplaceAll(s, ".", "")
	s = strings.ReplaceAll(s, ",", "")

	//fmt.Println(s)

	words := strings.Split(s, " ")
	presences := make(map[string]int)

	for _, word := range words {
		_, exists := presences[word]

		if exists {
			presences[word] += 1
		} else {
			presences[word] = 1
		}
	}

	fmt.Println(presences)

}
