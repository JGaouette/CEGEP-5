package _math

import (
	"sort"
)

func Somme(numbers []float64) float64 {
	somme := 0.0

	for i := 0; i < len(numbers); i++ {
		somme += numbers[i]
	}

	return somme
}

func Moyenne(numbers []float64) float64 {
	return Somme(numbers) / float64(len(numbers))
}

func EcartType(numbers []float64) float64 {
	moyenne := Moyenne(numbers)
	ecart := make([]float64, 0)

	for i := 0; i < len(numbers); i++ {
		if numbers[i] > moyenne {
			ecart = append(ecart, numbers[i]-moyenne)
		} else {
			ecart = append(ecart, moyenne-numbers[i])
		}
	}

	return Moyenne(ecart)
}

func Max(numbers []float64) float64 {
	max := numbers[0]

	for i := 0; i < len(numbers); i++ {
		if numbers[i] > max {
			max = numbers[i]
		}
	}

	return max
}

func Min(numbers []float64) float64 {
	min := numbers[0]

	for i := 0; i < len(numbers); i++ {
		if numbers[i] < min {
			min = numbers[i]
		}
	}

	return min
}

func Median(data []float64) float64 {
	dataCopy := make([]float64, len(data))
	copy(dataCopy, data)

	sort.Float64s(dataCopy)

	var median float64
	l := len(dataCopy)
	if l == 0 {
		return 0
	} else if l%2 == 0 {
		median = (dataCopy[l/2-1] + dataCopy[l/2]) / 2
	} else {
		median = dataCopy[l/2]
	}

	return median
}
