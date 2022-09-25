package main

import (
	"os"
	"testing"
)

var files, _ = os.ReadDir("./img")

func BenchmarkRecursiveThumbnail(b *testing.B) {
	for i := 0; i < b.N; i++ {
		recursiveThumbnail(files)
	}
}
