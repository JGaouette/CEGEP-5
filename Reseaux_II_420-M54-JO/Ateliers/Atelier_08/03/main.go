// Numéro 3
// Avec un RWMutex:
//
// Créez une variable numérique qui contient un chiffre.
//
// Créez 10 goroutines de lecture. Chacune "regarde" le chiffre durant 2 secondes
// puis l'affiche dans la console.
//
// Créez aussi 2 goroutines d'écriture. Chacune va modifier le chiffre.
//
// Pour bien voir ce qui se passe,
// affichez dans la console un message lorsqu'une goroutine "commence" son travail.
package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup
	var m sync.RWMutex
	num := 42

	for i := 1; i <= 2; i++ {
		wg.Add(1)
		go func(num *int, m *sync.RWMutex) {
			time.Sleep(time.Duration(rand.Intn(10)) * time.Second)

			fmt.Println("Start writing ...")

			defer wg.Done()
			m.Lock()
			defer m.Unlock()

			*num += *num / 2

			fmt.Println("Has written", *num)
		}(&num, &m)
	}

	for i := 1; i <= 10; i++ {
		wg.Add(1)
		go func(num *int, m *sync.RWMutex) {
			time.Sleep(time.Duration(rand.Intn(10)) * time.Second)
			fmt.Println("Start reading...")

			defer wg.Done()
			m.RLock()
			defer m.RUnlock()

			time.Sleep(2 * time.Second)
			fmt.Println("Read", *num)
		}(&num, &m)
	}

	wg.Wait()
}
