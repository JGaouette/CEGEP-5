package main

import (
	"flag"
	"fmt"
)

func main() {

	/*
		var deverminagePtr *bool
		var nbPtr *int

		flag.BoolVar(deverminagePtr, "v", false, "Afficher plus de détail")
		flag.IntVar(nbPtr, "nb", 0, "Afficher le nombre")
	*/

	deverminagePtr := flag.Bool("v", false, "Afficher plus de détail")
	nbPtr := flag.Int("nb", 0, "Afficher le nombre")

	flag.Parse()

	if *deverminagePtr {
		fmt.Printf("Plus de détail")
	}
	if *nbPtr != 0 {
		fmt.Printf("Encore plus de détail")
	}

	fmt.Println("Plus de détail")
}
