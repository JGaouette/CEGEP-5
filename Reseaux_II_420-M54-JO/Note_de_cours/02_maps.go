package main

import "fmt"

func main_02() {
	// Create slice instance
	var s = make([]int, 10, 20)

	// Create maps instance
	var x map[string]int = make(map[string]int)

	// Give and delete values
	x["clé"] = 10
	delete(x, "clé")

	fmt.Println(s)
	fmt.Println(x["clé"])

	elements := map[string]string{
		"H":  "Hydrogen",
		"He": "Helium",
		"Li": "Lithium",
		"Be": "Beryllium",
		"B":  "Boron",
		"C":  "Carbon",
		"N":  "Nitrogen",
		"O":  "Oxygen",
		"F":  "Fluorine",
		"Ne": "Neon",
	}

	// Get if element exists
	el, ok := elements["F"]
	fmt.Println(el, ok)

	// 2D maps
	elems := map[string]map[string]string{
		"H": {
			"name":  "Hydrogen",
			"state": "gas",
		},
	}

	fmt.Println(elems["H"])

	y := new(int)
	zero(y)
}

func zero(y *int) {
	*y = 0
}
