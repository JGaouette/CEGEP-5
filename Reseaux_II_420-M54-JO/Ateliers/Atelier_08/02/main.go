//Numéro 2
//Avec un mutex:
//Écrire une fonction qui écrit la phrase "Goroutine #X" une lettre à la fois
//(0.1 sec entre chaque lettre), X étant un numéro reçu en paramètre.
//
//Ensuite partir 10 goroutines qui attendent un nombre aléatoire de secondes entre 0 et 10
//puis appel la fonction d'écriture (donner le numéro de la goroutine en paramètre).
//
//Vous devez voir les 10 phrases bien écrits.

package main

import (
	"fmt"
	"strconv"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup
	var mutex sync.Mutex

	for i := 1; i <= 10; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()

			mutex.Lock()
			defer mutex.Unlock()

			toWrite := "Goroutine #" + strconv.Itoa(i)
			for _, c := range toWrite {
				fmt.Print(string(c))
				time.Sleep(100 * time.Millisecond)
			}
			fmt.Println()
		}(i)
	}

	wg.Wait()
}
