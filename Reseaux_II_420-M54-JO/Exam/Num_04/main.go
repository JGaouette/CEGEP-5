package main

import "fmt"

func main() {
	fmt.Println(Somme(2))
}

func Somme(n int) int {
	var somme int
	for i := 1; i*i < n; i++ {
		somme += i
	}
	return somme
}

/*
/// Test Unitaire avec échec///
=== RUN   TestSomme
    main_test.go:26: Attendu 3, Obtenu 1     //Devait être mauvais
    main_test.go:26: Attendu 36, Obtenu 28   //Devait être mauvais
--- FAIL: TestSomme (0.00s)

FAIL

/// Test Unitaire avec succès///
ok      num_04  0.196s

/// Benchmark ///
PASS
ok      num_04  0.188s
*/
