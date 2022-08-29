# Langage Go (introduction)

## Historique

Pour cette session, nous verrons le langage GO.

Ce langage est typé et compilable développé par Google en 2007. La version 1.0 est sortie en 2012, c'est un langage informatique relativement nouveau. Il est disponible sur de multiples plateformes de système d'exploitation: Windows, GNU/Linux, macOS, BSD, ...

## Particularités

Il ressemble au C/C++, mais il a une meilleure protection de la mémoire, un *garbage collector* et une meilleure gestion de la concurrence (de rouler plusieurs processus par la même application). Le dernier point étant particulièrement utile dans ce cours-ci étant donné que nous allons nous tourner vers de la programmation réseautique.

La majorité des exemples des notes peuvent facilement être copiés et collés sur le site: [https://play.golang.org/](https://play.golang.org/).

D'ailleurs vous avez la chance en chargeant cette page de voir le hello world:

```go
package main
import (
	"fmt"
)
func main() {
	fmt.Println("Hello, playground")
}
```

## Installation

### Solution native

Téléchargez go à partir du site officiel: [https://go.dev/](https://go.dev/).

### Solution Docker

À la racine de votre projet, créez un fichier **Dockerfile** avec ceci à l'intérieur:

```Dockerfile
FROM golang

WORKDIR /usr/src/app

COPY go.mod ./
RUN go mod download && go mod verify

COPY . .
RUN go build -v -o /usr/local/bin/app ./...

CMD ["app"]
```

Ensuite avec Goland vous pouvez appuyer sur la flèche verte en haut du fichier.
Avec VSCode, allez voir sur la documentation officielle: [https://hub.docker.com/_/golang/](https://hub.docker.com/_/golang/).

## Paquetage
Tous vos programmes sont réalisés en paquetages (*packages*) :

```go
package main

import (
	"fmt"
	"math/rand"
)
func main() {
	fmt.Println("My favorite number is", rand.Intn(10))
}
```

Ici, il y a deux paquetages qui sont importés (qui proviennent de la librairie de go), fmt pour le formatage et le paquetage Rand contenu dans le paquetage Math, comme nous pouvons le voir dans le lien suivant:

https://golang.org/pkg/math/

Permettant ainsi ici de segmenter nos paquetages aisément en fonction de nos besoins (nos applications go pourraient être subdivisé en plusieurs paquets pour alléger le code et pour simplifier sa conception. Nous y reviendrons ultérieurement.

Il est à savoir que les imports non utilisés feront que votre code ne compilera pas, ceci est voulu dans le sens que vous ne voulez pas garder des importations augmentant la taille de vos exécutables.
