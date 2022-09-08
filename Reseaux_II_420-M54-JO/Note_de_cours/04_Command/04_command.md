# Ligne de commande

## Drapeau (*flag*)

Une autre particularité des programmes est d'utiliser les flags, que sont les flags?

C'est une façon de passer des arguments à un programme, pour par exemple, permettre d'avoir des options de débugagges ou de verbosité.
Par exemple :

```
Exemple.exe -d
```

Pour retrouver si le d est activé ou non, nous utilisons une déclarons un flag d à l'intérieur de notre code:

```go
deverminagePtr:= flag.Bool("d", false, "bool de déverminage")
```

avant de réaliser:
 ```go
flag.Parse()
```

À partir de là nous pourrons obtenir la valeur de *d qui sera vraie ou fausse (il s'agit d'un pointeur).

Si vous voulez donner une valeur à votre flag (`exemple.exe -n=10`), vous devez utiliser une des solutions suivantes (les 2 lignes font la même chose):

```go
var nFlag = flag.Int("n", 1234, "help message for flag n")
flag.IntVar(&nFlag, "n", 1234, "help message for flag n")
```

Il faut ensuite appeler le `flag.Parse()` pour que nFlag contienne la valeur reçu.