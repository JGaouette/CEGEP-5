package main

import (
	"fmt"
	"github.com/nfnt/resize"
	"image/jpeg"
	"log"
	"os"
	"strings"
)

func main() {
	files, err := os.ReadDir("./img")
	if err != nil {
		log.Fatal(err)
	}

	recursiveThumbnail(files)
	threadsThumbnail(files)

}

func recursiveThumbnail(files []os.DirEntry) {
	for _, f := range files {
		if !f.IsDir() {
			fmt.Println(f.Name())

			file, err := os.Open("./img/" + f.Name())
			if err != nil {
				log.Fatal(err)
			}

			img, err := jpeg.Decode(file)
			if err != nil {
				log.Fatal(err)
			}

			m := resize.Resize(80, 80, img, resize.Lanczos3)

			out, err := os.Create("./img/thumbnail/" + strings.ReplaceAll(f.Name(), ".jpg", "") + "_thumbnail.jpg")
			if err != nil {
				log.Fatal(err)
			}

			jpeg.Encode(out, m, nil)
		}
	}
}

func threadsThumbnail(files []os.DirEntry) {
	for _, f := range files {
		go toThumbnail(f)
	}
}

func toThumbnail(entry os.DirEntry) {
	file, err := os.Open("./img/" + entry.Name())
	if err != nil {
		log.Fatal(err)
	}

	img, err := jpeg.Decode(file)
	if err != nil {
		log.Fatal(err)
	}

	m := resize.Resize(80, 80, img, resize.Lanczos3)

	out, err := os.Create("./img/thumbnail/" + strings.ReplaceAll(entry.Name(), ".jpg", "") + "_thumbnail.jpg")
	if err != nil {
		log.Fatal(err)
	}

	jpeg.Encode(out, m, nil)
}
