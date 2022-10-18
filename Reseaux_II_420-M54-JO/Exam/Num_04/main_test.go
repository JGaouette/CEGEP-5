package main

import "testing"

type paires struct {
	param, reponse int
}

var valeursTests = []paires{
	{1, 0},
	{2, 1},
	//{3, 3}, //Doit être mauvais
	{5, 3},
	{10, 6},
	{50, 28},
	{64, 28},
	//{64, 36}, //Doit être mauvais
	{65, 36},
}

func TestSomme(t *testing.T) {
	for _, paire := range valeursTests {
		f := Somme(paire.param)

		if f != paire.reponse {
			t.Errorf("Attendu %d, Obtenu %d", paire.reponse, f)
		}
	}
}

func benchmarkSomme(valeur int, b *testing.B) {
	for n := 0; n < b.N; n++ {
		Somme(valeur)
	}
}

func BenchmarkSomme1(b *testing.B) {
	benchmarkSomme(1, b)
}

func BenchmarkSomme5(b *testing.B) {
	benchmarkSomme(5, b)
}

func BenchmarkSomme10(b *testing.B) {
	benchmarkSomme(10, b)
}

func BenchmarkSomme50(b *testing.B) {
	benchmarkSomme(50, b)
}

func BenchmarkSomme64(b *testing.B) {
	benchmarkSomme(64, b)
}

func BenchmarkSomme65(b *testing.B) {
	benchmarkSomme(65, b)
}
