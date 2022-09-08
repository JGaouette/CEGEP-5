# Modules

Un module permet de réutiliser du code dans plusieurs projets. Par exemple un module pourrait contenir toutes nos fonctions mathématiques.

Historiquement, il fallait mettre des "paquetages" dans le GOPATH. Mais depuis la version 1.11 cette méthode n'est plus utilisé, on préfère les modules.

## Sous-dossier

Avant de voir les modules, comment utiliser plusieurs fichiers et dossiers dans un seul projet. Dans un projet, ça prend seulement une fonction `main`. Pour exécuter tous les fichier d'un dossier on roule la commande:

```
go run .
```

Pour un sous-dossier, il faut juste l'ajouter dans le import. Si votre fichier `go.mod` ressemble à:

```go
module awesomeProject

go 1.19
```

Et on veut inclure le dossier toto, dans notre fichier on l'importe:

```go
import "awesomeProject/toto"
```

Notez qu'on ne peut utiliser/importer que ce qui débute par une majuscule.

## Module local

Pour utiliser un module qui est sur votre ordinateur, mais pas dans votre dossier de travail, il faut ajouter à votre `go.mod`:

```go
replace crlj/math => ../math
```

Cette ligne va permettre d'utiliser un `import "crlj/math"` dans notre projet. Cet import pointe vers le dossier `../math`. Une fois utilisé, vous devrez exécuter la commande `go get` pour "télécharger" l'import.

Notez que je peux mettre un alias au module lorsque j'importe:

```go
import m "crlj/math"
```

## Module en ligne

On peut télécharger un module avec la commande suivante:

```go
go get rsc.io/quote
```

On pourrait aussi juste mettre l'import et utiliser le module, go va télécharger la dépendance à l'exécution. Par contre, l'auto-complétion ne fonctionnera pas avant d'exécuter une fois.

La dernière commande va chercher le paquet sur pkg.go.dev. Vous pouvez aussi mettre un lien github (sans https).

Pour retirer une dépendance, roulez la commande suivante qui va enlever les dépendances non-utilisés:

```
go mod tidy
```