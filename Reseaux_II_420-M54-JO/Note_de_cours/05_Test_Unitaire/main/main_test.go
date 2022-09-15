package main

import "testing"

// Fichier main_test.go

type paires struct {
	param, reponse int
}

var valeursTests = []paires{
	{0, 0},
	{10, 55},
	{4, 3},
}

func TestFibR(t *testing.T) {
	for _, paire := range valeursTests {
		f := FibR(paire.param)

		if f != paire.reponse {
			t.Errorf("Attendu %d, Obtenu %d", paire.reponse, f)
		}
	}
}

func TestFibT(t *testing.T) {
	f := FibR(10)
	if f != 55 {
		t.Errorf("Attendu 55, Obtenu %d", f)
	}
}

func benchmarkFibR(valeur int, b *testing.B) {
	for n := 0; n < b.N; n++ {
		FibR(valeur)
	}
}

func BenchmarkFibR1(b *testing.B) {
	benchmarkFibR(1, b)
}

func BenchmarkFibR5(b *testing.B) {
	benchmarkFibR(5, b)
}

func BenchmarkFibR10(b *testing.B) {
	benchmarkFibR(10, b)
}

func BenchmarkFibR50(b *testing.B) {
	benchmarkFibR(50, b)
}

func benchmarkFibT(valeur int, b *testing.B) {
	for n := 0; n < b.N; n++ {
		FibT(valeur)
	}
}

func BenchmarkFibT1(b *testing.B) {
	benchmarkFibT(1, b)
}

func BenchmarkFibT10(b *testing.B) {
	benchmarkFibT(10, b)
}

func BenchmarkFibT100(b *testing.B) {
	benchmarkFibT(100, b)
}

func BenchmarkFibT1000(b *testing.B) {
	benchmarkFibT(1000, b)
}
