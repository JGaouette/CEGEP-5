# Kotlin
Depuis quelques années, Kotlin est le langage de prédilection pour le développement sur Android, par contre, il n'est pas uniquement disponible pour les applications Android:

* Développement web
* Côté serveur
* Science

En gros, puisqu'il compile en code binaire JVM, c'est Java 2.0. Il a cependant les avantages suivant:

* Multiplateforme (provient de Java)
* Compatible avec Java (vous pouvez utilisez du code Java dans Kotlin)
* Il fut créé par JetBrains en 2011. Google annonce en 2017 que Kotlin devient le second langage pris en charge par Android et pas plus loin que 2 ans plus tard, il remplace Java.
* Gratuit
* Facile à apprendre
* Concis (dans le sens que le nombre de ligne de code pour parvenir au même résultat est largement inférieur)

## Syntaxe

```
// Commentaire

/* Très long
 * Commentaire
 */ 

fun main() {
  println("Hello World")
}
```

* **fun** est pour déclarer la fonction
* **main** indique le début de la fonction
* **println** est une méthode qui affiche sur la console (en insérant une ligne vide à la fin)

* Pas de ;
* Pas besoin d'une classe
* Pas besoin d'argument à la fonction main
* Pas besoin de spécifier la classe statique

## Variable

```
var greeting = "Hello Kotlin"
println(greeting)
```

Il y aurait une erreur si vous tentez par la suite de faire:

```
var greeting = "Hello Kotlin"
println(greeting)
greeting = 1
```

https://pl.kotl.in/P5Nmb4jMw

Pour spécifier le type directement à l'assignation

```
var greeting : String
```

### Final

Les valeurs finales sont des constantes, des valeurs immuables. 

Il est recommandé en Kotlin d'utiliser le maximum de variable finale:

```
val test = "Bonjour"
```

### Comparaisons 

Vous n'avez pas non plus à vous en faire pour les comparaisons:

Que donnera en java le code suivant?

```
Integer a = 1000
Integer b = 1000

System.out.println(a == b)
```

https://www.online-java.com/72FVXEBdTz

Car les deux types n'ont pas la même référence. Pour comparer que la valeur en Java, il fallait utiliser le a.equals(b).

En Kotlin

```
val a = 1000
val b = 1000

print (a == b)
```

https://pl.kotl.in/3lFof2kIh

### Fonctions

```
fun getGreeting(): String {
  return "Hello, Kotlin"
}

fun main(){
  println(getGreeting())
}
```

https://pl.kotl.in/OTrZBpHDi

Pour simplifier l'écriture de la fonction (surtout lorsqu'elle a juste une ligne)
```
fun getGreeting() = return "Hello, Kotlin"
```

## NPE - Null Pointer Excepiton

Un gros problème était qu'en java si un objet était Null il pouvait crasher à l'exécution

```
final String s = null;
System.out.println(s.length());
```

Tel que démontré ici:

https://www.online-java.com/DbEZ9n8CV6

Alors qu'en Kotlin, il vérifie à la compilation pour les types Null.

```
val s: String = null // Ne compilera pas.
```

## List

C'est un ensemble ordonnée d'éléments du même type. La séquence dans une liste est importante.

```
val hobbits = listOf("Frodo", "Sam", "Pippin", "Merry")
ou
val hobbits: List<String> = listOf("Frodo", "Sam", "Pippin", "Merry")

println(hobbits)
```

Puisque la liste est immuable, elle supporte la possibilité d'ajouter à une liste en créant une nouvelle liste

```
hobbits = hobbits.plus("Joe")
```

https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-list/

## Sets

Plus rapide qu'une liste mais sans la possibilité d'indexage. Pas de garantie de conservation de l'ordre. De plus, un set ne supporte pas les doublons.

```
val etudiants = setOf("D'Amato, Nikolas",
"Daoust, Gabriel",
"Dubuc, Eugène-Emmanuël",
"Dufresne, Gabriel",
"Gagnon, Marc-Antoine",
"Gaouette, Jérémy",
"Lambert, William-Benoît",
"Laporte, Thomas",
"Maestre Ariza, Bryan",
"Miguel-Gagnon, Jean-Philippe",
"Perreault, Jérémie",
"Phoenix-Lefebvre, Olivier",
"Provost, Isabelle",
"Rail, Raphaël",
"Raymond-Plourde, Gabriel",
"Richer, Ulric",
"Savoie, Olivier",
"Sincerny, Raphaël",
"Veillette, Louis-Félix")

println("Joe" in etudiants)
```

https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-set/

## Maps

Liste d'éléments reliés de façon clé-valeur, tel un dictionnaire.

```
val movieBatmans = mapOf(
"Batman Returns" to "Michael Keaton",
"Batman Forever" to "Val Kilmer",
"Batman & Robin" to "George Clooney"
)
println(movieBatmans["Batman Returns"])
> true

println(" Batman Begins " !in movieBatmans)
> true
```

https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-map/

## Mutables

Par défaut, les types que nous venons de voir sont immuables, donc ils ne peuvent être modifiés par le code. On ne peut donc pas non plus leur ajouter ou supprimer des éléments.


### MutableList

Cependant, il nous est possible d'utiliser les MutableList qui permet d'obtenir des objets qui peuvent être modifiables directement.

```
	var hobbits: MutableList<String> = mutableListOf<String>("Frodo", "Sam", "Pippin", "Merry")
    
  hobbits.add("Joe")

  println(hobbits)
```

https://pl.kotl.in/utWPST7SF


### mutableMap

```
	val movieStarWars: MutableMap<String,String> = mutableMapOf(
        "Star Wars Episode 4" to "Luke Skywalker",
        "Star Wars Episode 5" to "I am your father",
        "Star Wars Episode 6" to "Anakin est sauvé",
        )

    
    movieStarWars.put("Star Wars Episode 9", "J'ai les powers de tous les jedis sans avoir rien étudier")

    println(movieStarWars["Star Wars Episode 9"])

```

Les opérations sur les maps muables sont les suivantes:
* put, putAll
* Merge (Update)
* remove
* filter

## Arrays

Tableau immuable de données

```
val musketeers: Array<String> = arrayOf("Athos", "Porthos", "Aramis")

ou 

// Crée un Array<String> avec les valeurs ["0", "1", "4", "9", "16"] en lui passant la méthode (i*i)
val asc = Array(5) { i -> (i * i).toString() }
```

### Muable: Arraylist

```
// creating empty arraylist using constructor
var repasPrefere = ArrayList<String>()
arraylist.add("Poutine")
 
arraylist.add("Pizza")
```
* add


## Flow

### if 

Le if est plutôt traditionnel

```
var max = a
if (a < b) max = b

// With else
var max: Int
if (a > b) {
    max = a
} else {
    max = b
}

// As expression
val max = if (a > b) a else b
```

### when

Il s'agit d'un case déguisé avec la possibilité d'assignation immédiate.

```
val day = 4

val result = when (day) {
  1 -> "Monday"
  2 -> "Tuesday"
  3 -> "Wednesday"
  4 -> "Thursday"
  5 -> "Friday"
  6 -> "Saturday"
  7 -> "Sunday"
  else -> "Invalid day."
}
println(result)
```

### for

```
val cars = arrayOf("Volvo", "BMW", "Ford", "Mazda")
for (x in cars) {
  println(x)
}

for (chars in 'a'..'x') {
  println(chars)
}

```

# Méthode de communication avec la ligne de commande

readln()
println()