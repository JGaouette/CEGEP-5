package main

import (
	"fmt"
	"math"
)

// ! Cercle et Rectangle hérite de Forme
type Forme interface {
	aire() float64
}

func aireTotal(formes ...Forme) float64 {
	var total float64
	for _, f := range formes {
		total += f.aire()
	}
	return total
}

// ! Structure de Cercle
type Cercle struct {
	x, y, r float64
}

func (c *Cercle) aire() float64 {
	return math.Pi * c.r * c.r
}

// ! Structure de Rectangle
type Rectangle struct {
	x1, y1, x2, y2 float64
}

func (r *Rectangle) aire() float64 {
	return (r.x2 - r.x1) * (r.y2 - r.y1)
}

// ! Héritage réel -> Prof hérite de Employe
type Employe struct {
	nom string
	no  int
}

func (e *Employe) salutation() string {
	return e.nom + " sup"
}

type Prof struct {
	codeAcces string
	Employe
}

func main() {
	c := Cercle{0, 0, 5}
	r := Rectangle{0, 0, 20, 20}

	//? Les structeurs sont pointeurs
	fmt.Println(c.aire())
	fmt.Println(r.aire())

	//? Les interfaces doivent être appelé avec &
	fmt.Println(aireTotal(&c, &r))

	p := Prof{
		codeAcces: "asdf",
		Employe: Employe{
			nom: "Phil",
			no:  42,
		},
	}

	fmt.Println(p.salutation())
}
