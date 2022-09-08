# Maps et pointeurs

## Maps

Dernier type de base du langage go, il s'agit d'une liste de clé -> valeur non ordonnée (quelques fois nommée dans d'autres langage: tableau associatif, hash tables ou dictionnaires). Le but d'une map est de rechercher un objet par sa clé. Ils sont définis ainsi:

```go
var x map[string]int
```

Le but de cette déclaration sert à définir un tableau d'entier, indexé par des chaînes. C'est une map de chaîne vers des entiers. Tout comme les tableaux, elles sont définies avec des crochets:

```go
var x map[string]int
x["clé"] = 10
fmt.Println(x)
```
Ce code devrait créer une erreur d'exécution comme l'indique le message d'erreur suivant:

```
PS go run .\map.go 
panic: assignment to entry in nil map 
```

Pourquoi? Puisqu'il s'agit d'un type particulier, il doit être "instancié" avant d'être utilisé.

voici le correctif à utiliser:

```go
var x = make(map[string]int)
x["clé"] = 10
fmt.Println(x["clé"])
```

Le code va exécuter et afficher 10. L'instruction make a la signature suivante pour les maps:

```go
make(type)
```

La commande permet d'initialiser le map afin que l'on puisse commencer à le remplir. Finalement, ça réserve l'espace en mémoire afin qu'on puisse l'utiliser. La même commande peut être utilisée pour la création des slices, par contre, elle a une notation différente:

```go
make(type, longueur, capacité)
```

Une notion importante de comprendre est la différence entre la longueur et la capacité. La longueur est la quantité de données dans le slice en cours. La capacité est la longueur totale que peut avoir le slice (n'oubliez pas que vu qu'il pointe vers un tableau (ou un autre slice), elle ne peut être plus grande que la capacité totale du tableau original.

Le code va précédent retourne une map à laquelle il sera possible d'ajouter des éléments et de les supprimer par l'entremise de:

```go
delete(x,"clé")
```

Cette commande permet de supprimer de la map x, l'élément clé. Supposons que vous avez le map suivant:

```go
elements := make(map[string]string)
elements["H"] = "Hydrogene"
elements["He"] = "Helium"
elements["Li"] = "Lithium"
elements["Be"] = "Beryllium"
elements["B"] = "Bore"
elements["C"] = "Carbone"
elements["N"] = "Nitrogene"
elements["O"] = "Oxygene"
elements["Ne"] = "Neon"
elements["F"] = "Fluorine"
fmt.Println(elements["Li"])
```

Sans attente, le code va retourner Lithium, mais que ce passe-t-il si nous essayons de recouvrer un élément inexistant:

```go
fmt.Println(elements["Un"])
```

Il va retourner une chaîne vide. Une meilleure façon d'approcher ce résultat sera de faire une pré-assignation:

```go
name, ok := elements["Un"]
fmt.Println(name,ok)
```

Go va retourner par défaut une seconde valeur, un booléen, indiquant true s'il trouve l'élément, et false dans l'inverse. Ainsi le retour va indiquer si l'assignation va fonctionner, il n'est pas rare de voir dans les tests de go:

```go
if name, ok := elements["Un"]; ok {
    fmt.Println(name, ok)
}  
```

Donc ceci va fonctionner uniquement dans le cas que le if sera vrai, donc n'affichera rien dans le cas contraire (N'oubliez pas le if, l'assignation se passe en premier, ensuite le test (qui est juste la variable booléenne ok, et finalement l'affichage si c'est à vrai). La durée de vie de name et de ok n'est que pour le if. En réalité, ce qui se passe ressemble à ceci:

```go
name, ok := elements["Un"];
if ok {
    fmt.Println(name, ok)
}
```

Il est possible également de créer des maps plus rapidement que ce que vous avez vu précédemment (sans le make, mais en définissant les éléments directement):

```go
elements := map[string]string{
    "H": "Hydrogen",
    "He": "Helium",
    "Li": "Lithium",
    "Be": "Beryllium",
    "B": "Boron",
    "C": "Carbon",
    "N": "Nitrogen",
    "O": "Oxygen",
    "F": "Fluorine",
    "Ne": "Neon",
}
```

Pour rendre ça encore plus palpitant comme langage, il est possible également de faire une map chaîne, pointant à une map de chaîne pointant à une chaîne:

```go
elements := map[string]map[string]string){  
   "H": map[string]string{
        "name":  "Hydrogen",
        "state": "gas",
    },        
   "He": map[string]string{
        "name":  "Helium",
        "state": "gas",
    },       
    "Li": map[string]string{
        "name":  "Lithium",
        "state": "solid",
    },
    "Be": map[string]string{
        "name":  "Beryllium",
        "state": "solid",
    },
    "B": map[string]string{
        "name":  "Boron",
        "state": "solid",
    },
    "C": map[string]string{
        "name":  "Carbon",
        "state": "solid",
    },
    "N": map[string]string{
        "name":  "Nitrogen",
        "state": "gas",
    },
    "O": map[string]string{
        "name":  "Oxygen",
        "state": "gas",
    },
    "F": map[string]string{
        "name":  "Fluorine",
        "state": "gas",
    },
    "Ne": map[string]string{
        "name":  "Neon",
        "state": "gas",
    },
 }

        
 if el, ok := elements["Li"]; ok {
    fmt.Println(el["name"], el["state"])
 }
 ```

La map externe sert de référence vers l'élément du tableau qui pointe vers une map d'information comme son nom et son type. Bien que les maps peuvent être utiles dans plusieurs situations, dans quelques instants nous verrons un nouveau type qui sera bien plus applicables dans nos cas de développement.

# Pointeurs et références

Soit le code suivant:

```go
func zero(x int) {
    x = 0
}

func main() {
    x := 5
    zero(x)
    fmt.Println(x) // x est toujours 5
}
```

Bien que cela semble bizarre, il faut comprendre ici que la fonction zero (qui met à 0 l'argument reçu en paramètre), ne reçoit pas le x de la fonction main, mais bien une copie de cette valeur. Vous vous en êtes sans doute rendu compte lorsque vous avez fait votre tri en bulle, si vous avez essayer de le faire dans une méthode.

Comme vous vous êtes si bien amusé avec les pointeurs avec les cours de Patrick, ils sont de retour dans ce cours-ci. Pour recevoir le pointeur de notre x dans la méthode zéro, il faut donc recevoir une adresse à l'intérieur de la méthode zero et passer l'adresse dans notre main:

```go
func zero(xPtr *int) {
    *xPtr = 0
}

func main() {
    x := 5
    zero(&x)
    fmt.Println(x) // x est 0
}
```

Vous comprendrez donc l'importance de bien choisir le bien comprendre le fonctionnement lors de vos méthodes. Le * a deux fonctionnalités dans ce code:

1. Identifier qu'une donnée sera un pointeur vers le type (par après). Le xPtr n'est pas une variable int, mais bien un pointeur vers une donnée Int.
2. Lors de l'utilisation de *xPtr, c'est une méthode de déférencement du pointeur, i-e qu'on retrouve la donnée pointée par le xPtr et qu'on obtient donc, sa valeur. Ici, la valeur est modifiée vers 0.

Alors que le & permet d'obtenir l'adresse d'une variable, c'est l'adresse de la variable x qui est passée à la méthode zero.

## new

Une autre fonctionnalité intéressante est l'utilisation du mot-clé new:

```go
func one(xPtr *int) {
    *xPtr = 1
}

func main() {
    xPtr := new(int)
    one(xPtr)
    fmt.Println(*xPtr) // x est 1
}
```

Ici la fonction main, crée un pointeur vers un entier, on passe cet objet directement à la méthode one qui se fait modifier. Par contre, pour pouvoir afficher le contenu de xPtr, nous devons le déférencer.