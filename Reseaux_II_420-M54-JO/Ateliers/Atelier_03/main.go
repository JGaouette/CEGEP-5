package main

import (
	"fmt"
	"math"
)

func main() {
	cercle := Cercle{0, 0, 5}
	rectangle := Rectangle{0, 0, 20, 20}
	carre := Carre{15}

	//? Les structeurs sont pointeurs
	fmt.Println(cercle.aire())
	fmt.Println(rectangle.aire())
	fmt.Println(carre.aire())

	//? Les interfaces doivent être appelé avec &
	fmt.Println(aireTotal(&cercle, &rectangle, &carre))
	fmt.Println(perimetreTotal(&cercle, &rectangle, &carre))
}

// ! Cercle et Rectangle hérite de Forme
type Forme interface {
	aire() float64
	perimetre() float64
}

func aireTotal(formes ...Forme) float64 {
	var total float64
	for _, f := range formes {
		total += f.aire()
	}
	return total
}

func perimetreTotal(formes ...Forme) float64 {
	var total float64
	for _, f := range formes {
		total += f.perimetre()
	}
	return total
}

// ! Structure de Cercle
type Cercle struct {
	x, y, r float64
}

func (cercle *Cercle) aire() float64 {
	return math.Pi * cercle.r * cercle.r
}

func (cercle *Cercle) perimetre() float64 {
	return 2 * math.Pi * cercle.r
}

// ! Structure de Carre
type Carre struct {
	h float64
}

func (carre *Carre) aire() float64 {
	return carre.h * carre.h
}

func (carre *Carre) perimetre() float64 {
	return carre.h * 4
}

// ! Structure de Rectangle
type Rectangle struct {
	x1, y1, x2, y2 float64
}

func (rect *Rectangle) aire() float64 {
	return (rect.x2 - rect.x1) * (rect.y2 - rect.y1)
}

func (rect *Rectangle) perimetre() float64 {
	return (rect.x2-rect.x1)*2 + (rect.y2-rect.y1)*2
}
