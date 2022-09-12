# NPE (Null Pointer Exception)

La façon que kotlin est codée vise à éviter les erreurs de référencement de type null.

https://en.wikipedia.org/wiki/Tony_Hoare#Apologies_and_retractions

Les seules façons d'obtenir un NPE en kotlin est:

* throw NullPointerException()
* utilisation des !!
* L'inconsistance des données (un this non-initialisée)
* Avec Java

En Kotlin, on peut déterminer à la création de la variable si une variable peut être de type null:

```
var a: String = "abc" // Regular initialization means non-null by default
a = null // compilation error

var b: String? = "abc" // can be set to null
b = null // ok
print(b)

```

https://pl.kotl.in/0yrEX_riu


Même si vous tentez ultérieurement d'appeler une méthode d'un objet, c'est garanti qu'elle ne se fera jamais appelée sur un objet null (causant l'exception).

```
val l = b.length 
```

https://pl.kotl.in/_jsdhAAyY


## Validation de null sur un objet

### if

```
val l = if (b != null) b.length else -1
```

### safe case

Le safe case est identique au précédent sauf avec juste une opération. Cela permet de retourner null au lieu de retourner de ne pas fonctionner.

```
val a = "Kotlin"
val b: String? = null

println(b?.length)
println(a?.length) // Unnecessary safe call
```

Surtout pratique dans l'utilisation de plusieurs chaînes successives:

```
bob?.department?.head?.name
```

Si une des parties est null, la chaîne complète retourne null.

### Elvis

Revenons à notre test précédent:

```
val l = if (b != null) b.length else -1
```

Nous pourrions mélanger avec ce que nous venons d'apprendre avec le safe case:

```
val l = b?.length ?: -1
```

On introduit alors on safe case et une alternative. Nous avons notre opérateur elvis ?: . En gros ça vérifie si le côté gauche est null, si oui, donne le côté droit.

### !!

L'opérateur !! est pour ceux qui veulent risquer d'obtenir des exceptions NPE. Il permet de s'assurer que si la valeur de gauche est null, une exception est générée.