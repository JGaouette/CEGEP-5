//Numéro 1
//Avec une opération atomique:
//Faire une boucle simple de 1 à 1.000 qui crée des goroutines.
//Comptez tous les nombres qui sont multiples de 3 ou de 5.

package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

func main() {
	var wg sync.WaitGroup
	var nb int32 = 0

	for i := 1; i <= 1000; i++ {
		wg.Add(1)
		go func(i int, nb *int32) {
			defer wg.Done()
			if i%3 == 0 || i%5 == 0 {
				atomic.AddInt32(nb, 1)
			}
		}(i, &nb)
	}
	wg.Wait()

	fmt.Println("Il y a", nb, "multiples de 3 ou 5")
}
