package main

import "fmt"

type Paladin struct {
	nom     string
	pv      int
	attaque int
	defense int
}

func (p *Paladin) Status() (bool, string) {
	if p.pv > 0 {
		if p.attaque > p.defense {
			return true, "offensif"
		} else if p.defense > p.attaque {
			return true, "defensif"
		} else {
			return true, "balance"
		}
	}
	return false, "mort"
}

type Chevalier interface {
	Status() (bool, string)
}

func main() {
	p := Paladin{"Paladin", 100, 100, 1110}
	AfficherStatut(&p)
}

func AfficherStatut(c Chevalier) {
	_, statut := c.Status()
	fmt.Println(statut)
}
