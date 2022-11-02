# Langage de programmation Swift

## Selon Wikipédia

Swift est un langage de programmation objet compilé, multi-paradigmes, qui se veut simple, performant et sûr. Il est développé en open source.

Le projet de développement de Swift est géré par Apple, qui en est également le principal contributeur ; mais de nombreux membres de la communauté Swift, ainsi que d'autres acteurs, tels que Google et IBM, participent également à son développement. Swift est officiellement supporté sur les systèmes d'exploitation Ubuntu, iOS, macOS, watchOS et tvOS. Un support non officiel (géré par la communauté) existe pour d'autres plateformes Linux, telles que Debian et Fedora.

* Un manuel officiel en anglais est disponible en ligne: https://docs.swift.org/swift-book/LanguageGuide/TheBasics.html

* Un swift playground est disponible ici pour tester le code: http://online.swiftplayground.run/ 

Swift dispose d'une interopérabilité avec le langage C ainsi qu'avec l'Objective-C sur les plateformes d'Apple.

## Historique
Le développement de Swift a été commencé en 2010 par Chris Lattner et prend ses sources dans de nombreux langages de programmation tels qu'Objective-C, Haskell, Ruby, Python, Caml ou C#. La première version publique (1.0) a été publiée le 2 juin 2014 à la WWDC 2014.

En juin 2015, Apple annonce le passage en open source du langage Swift lors de la WWDC 2015, et celui-ci sera effectif en décembre de la même année. La version 3.0 de Swift est lancée en septembre 2016. La version 4.0 est disponible depuis le 19 septembre 2017 et se concentre principalement sur la stabilité de la syntaxe du code source. La version 5 est apparue en 2019 et apporte principalement la stabilisation de l'interface. 

Nous en sommes rendus à la version 5.5 qui a été annoncée par Apple en 2021 permettant la concurrence et le code asynchrone.

## Déclaration

* var est une variable
* let est une constante

```
var maVariable = 42
maVariable = 50
let maConstante = 42
```

Vous pouvez déclarer une multitude de variable sur la même ligne:

```
var x = 0.0, y = 0.0, z = 0.0
```


Si vous souhaitez indiquer le type de la variable:

```
var welcomeMessage: String
var red, green, blue : Double
```

Vous pouvez utiliser n'importe quel caractère unicode pour l'écriture de vos variables

```
let π = 3.14159
```

Il est possible d'assigner une multitude de valeur à la fois, par exemple pour un tuple:

```
let (x, y) = (1, 2)
```

Le langage est fortement typé, une fois le type déduit, il ne peut plus être changé. Dès qu'une valeur est constante, vous devez utilisez let.

## Affichage 

Pour afficher le contenu d'une variable:

```
print (var)
```

Vous n'êtes pas obligés d'inclure un ; après chacune de vos commandes. Vous pouvez si vous le désirez, cependant, si vous souhaitez exécuter plus d'une commande dans la même ligne, vous devrez les inclure entre les deux commandes:

```
let cat = ""; print (cat)
```

## Type de variables

Swift vous offre accès aux entiers Int, Int8, Int16, Int32, Int64. De façon générale, il est suggéré d'utiliser uniquement Int plutôt que de spécifier sa taille.

De même, il est possible d'avoir accès au UInt, mais de façon générale, il est préférable d'utiliser Int plutôt que UInt  pour favoriser l'interopérabilité du code.

Float et Double sont également disponibles afin de représenter vos calculs arythmétiques.

De façon générale, Swift est un langage typé, dans le sens que vous ne pouvez passer un Int à une méthode qui demande une String.

L'inférence de type est la façon que Swift détermine le type que vous utilisez, surtout lors de la déclaration de variable:

```
// meaningOfLife est un Int
let meaningOfLife = 42


// pi est un double. Sans spécification, les nombres à virgules sont des doubles.
let pi = 3.14159

// Un autre type est le Booléen: Bool.
// Vous ne pouvez violez l'idée d'un booléen:


let i = 1
if i {
  // Ceci ne fonctionne pas. Alors que i == 1 aurait fonctionné
}
```

### String

Une string peut être assignée directement

```
let someString = "Some string literal value"
```

Ou avoir plusieurs lignes:
```
let quotation = """
  The White Rabbit put on his spectacles. "Where shall I begin, please your Majesty?" he asked.
  "Begin at the beginning," the King said gravely, "and go on till you come to the end; then stop."

"""
```

Vous pouvez faire certaines opérations sur les chaînes:

```
var variableString = "Horse"
variableString += " and carriage"
```

ou concaténation:

```
let string1 = "hello"
let string2 = " there"
var welcome = string1 + string2
// welcome now equals "hello there"
```

Elles sont de type valeur: si vous créez une chaîne basée sur une chaîne actuelle, c'est la valeur (le contenu) de la chaîne actuelle qui est passée à la copie.

```
for character in "Dog!" {
  print(character) }
// D
// o
// g
// !
//
```

## Interpolation

En préfixant une variable par (\ ... ) , vous effectuer une transition vers une chaîne:

```
let multiplicateur = 3
let message = "\(multiplicateur) x 2.5 est \(Double(multiplicateur) * 2.5)"
print (message)
// Affiche "3 x 2.5 is 7.5"
```

Ce qu'il faut comprendre ici \(multiplicateur) retourne une chaîne "3" alors que Double(multiplicateur) retourne 3 (en double) * 2.5 et le résultat de ce calcul est retourné en tant que chaîne en utilisant \(...).

## Count

Pour compter les éléments d'une chaîne, vous pouvez utiliser le .count sur la chaîne.

Plusieurs autres méthodes sont disponibles sur les chaînes:

```
var welcome = "hello"
welcome.insert("!", at: welcome.endIndex)
let greeting = "Hello, world!"
let index = greeting.firstIndex(of: ",") ?? greeting.endIndex
let beginning = greeting[..<index]
// welcome est "hello!"
// beginning est "Hello"
```

On va revenir plus tard sur la syntaxe ??, sachez seulement que ça représente soit la première occurence de la virgule ou l'index de fin de la chaîne **greeting**.

# Tuples

Finalement, un nouveau type: Tuples est un regroupement de valeur. 

```
// Erreur web
let http404Error = (404, "Not Found")

// le nom et l'âge
let nameAndAge = (name:"Midhun", age:7)

// Il est possible d'y accéder en utilisant: 

nameAndAge.name
nameAndAge.age

// Ou sinon, si l'on ne définit pas les noms de ses éléments, on peut les indexer:

let nameAndAge = ("Midhun", "7")
nameAndAge.0
nameAndAge.1

let (theName, theAge) = nameAndAge
theName
theAge
```

Ils sont particulièrement utiles dans le retour d'une fonction. La fonction qui indique deux données lors de son retour donne plus d'information que si elle ne retournait qu'un seul int.

Vous pouvez stocker des tuples à l'intérieur d'un tuples ou même un dictionnaire:

```
var alphabets = ("A", "B", "C", ("a", "b", "c"))

// access first element
print(alphabets.0)   
// "A"

// access the third element
print(alphabets.3)
//("a","b","c")

// access nested tuple
print(alphabets.3.0)  
// "a"

// Nous verrons le dictionnaire un peu plus tard

var laptopLaunch = ("MacBook", 1299, ["Nepal": "10 PM", "England": "10 AM"])

print(laptopLaunch.2)
// ["Nepal": "10 PM", "England": "10 AM"]


laptopLaunch.2["USA"] = "11 AM"

print(laptopLaunch.2)
// ["Nepal": "10 PM", "England": "10 AM", "USA": "11 AM"]
```

# Collection

Pour la gestion des collections, Swift vous offre 3 éléments de base: Array, Set et Dictionnaires. Les valeurs sont toujours typés et vous ne pouvez insérer ou obtenir un type de valeur différent dans la collection.

![](images/CollectionTypes_intro_2x.png)

## Array

Voici des exemples concrets sur la création de tableaux en Swift:

```
var someInts: [Int] = []
print("someInts is of type [Int] with \(someInts.count) items.")

var shoppingList: [String] = ["Oeufs", "Lait"]
```

Plusieurs méthodes existent pour la gestion des arrays: isEmpty, count, append, insert, ...

De plus, vous pouvez aussi utiliser l'opérateur += pour ajouter des éléments.

```
shoppingList += ["Chocolat"]
shoppingList.append("Vanille")

```

Étant donné que les valeurs sont indexés, vous pouvez utiliser l'opérateur [] pour rechercher un élément particulier. Les index doivent être valides:

```
shoppingList[2...3] = ["Bananes", "Pommes"]
for item in shoppingList {
  print(item)
}
```


## Optional

Vous pouvez utiliser un optionals dans le cas qu'une valeur peut être absente (null). L'optionnel représente deux possibilités, soit qu'il y a une valeur et qu'il est possible de l'obtenir en unwrappant ou qu'il n'y a aucune valeur (nil) :

```
let possibleNumber = "123"
let convertedNumber = Int(possibleNumber)
```

Puisqu'il est possible que la conversion ne fonctionne pas, le type sera Int? et non Int. Il ne peut rien contenir d'autre qu'un Int: soit c'est un Int, soit c'est nil.

```
var serverResponseCode: Int? = 404
serverResponseCode = nil
```
Vous ne pouvez utiliser nil avec une variable ou une constante non-optionnelle.

La déclaration d'un objet ainsi: 

```
var surveyAnswer: String?
// surveyAnswer est nil
```

Pour obtenir les valeurs d'un Optional, vous devez utiliser le !:

```
if convertedNumber != nil {
  print("convertedNumber has an integer value of \(convertedNumber!).")
}
```

De façon plus élégante, on utilise les conversions optionnelles (Optional Binding):

Supposons que possibleNumber est une chaîne pouvant être un Int.
```
var possibleNumber : String? = "42"

if let possibleNumber = possibleNumber{
  if let actualNumber = Int(possibleNumber) {
    print("The string \(possibleNumber) has an integer value of \(actualNumber)")
  } else {
    print("The string \(possibleNumber) couldn't be converted to an integer")
  }
}
```

Il est possible d'imbriquer les if let également:

```
if let firstNumber = Int("4") {
  if let secondNumber = Int("42") {
    if firstNumber < secondNumber && secondNumber < 100 {
      print("\(firstNumber) < \(secondNumber) < 100")
    }
  }
}
```

## Opérateur

Les opérateurs traditionnels sont fonctionnels :

* Arithmetique (+, -, *, /, %)
* Unitaire (+, -)
* Comparaison( ==, !=, >, <, >=, <=)
* Logique (!a, a && b, a || b)
* Tertiaire (question ? sivrai : sifaux)
* Fusion (a ?? b)

### Opérateur fusion

```
a != nil ? a! : b
```

Si a n'est pas nul, alors a sinon b.  

D'une façon plus commune, on utilise le fusion dans le cas de vouloir assigner une valeur par défaut:

```
let defaultColorName = "red"
var userDefinedColorName: String? // defaults to nil

var colorNameToUse = userDefinedColorName ?? defaultColorName
```

Afin d'avoir une variable colorNameToUse toujours définie et celle de l'utilisateur si cette dernière est définie.

# Boucles 

## Range (a..b)
```
for index in 1..5 
  va boucler de 1 à 5

for a..<b 
  va boucler de a à b sans inclure b

let names = ["Anna", "Alex", "Brian", "Jack"]
let count = names.count

for i in 0..<count {
    print("Person \(i + 1) is called \(names[i])")
}

for name in names[2...] {
  print(name)
}
// Brian
// Jack

for name in names[...2] {
  print(name)
}
// Anna
// Alex
// Brian

for name in names[..<2] {
  print(name)
}
// Anna
// Alex
```

### for in loops

```  
let names = ["Anna", "Alex", "Brian", "Jack"]

for name in names {
  print("Hello, \(name)!")
}

// Hello, Anna!
// Hello, Alex!
// Hello, Brian!
// Hello, Jack!

for index in 1...5 {
  print("\(index) times 5 is \(index * 5)")
}

// 1 times 5 is 5
// 2 times 5 is 10
// 3 times 5 is 15
// 4 times 5 is 20
// 5 times 5 is 25
```


## While

![](images/snakesAndLadders_2x.png)
```
board[03] = +08 
board[06] = +11 
board[09] = +09 
board[10] = +02
board[14] = -10 
board[19] = -11
board[22] = -02
board[24] = -08

var square = 0
var diceRoll = 0
while square < finalSquare {
  // roll the dice
  diceRoll += 1
  if diceRoll == 7 { diceRoll = 1 }
  // move by the rolled amount
  square += diceRoll
  if square < board.count {
    // if we're still on the board, move up or down for a snake or a ladder
    square += board[square]
  }
}
print("Game over!")
```

### repeat ... while
```
repeat {
  // move up or down for a snake or ladder
  square += board[square]
  // roll the dice
  diceRoll += 1
  if diceRoll == 7 { diceRoll = 1 }
    // move by the rolled amount
    square += diceRoll
} while square < finalSquare
print("Game over!")
```

# Contrôle

## Switch

Le switch est relativement traditionnel, mais l'utilisation d'un tuple peut s'avérer très intéresant:

```
switch var {
    case value 1:
        respond to value 1
    case value 2, value 3:
        respond to value 2 or 3
    default:
        otherwise, do something else
}
```

La seule particularité est qu'il n'y a pas de fallthrough, dans le sens qu'en C nous devons obligatoirement utiliser le break pour quitter le switch et ne pas aller au prochain énoncé. En Swift, c'est l'inverse, si on n'indique pas le fallthrough, il n'y aura pas de continuité: 

```
let integerToDescribe = 5
var description = "The number \(integerToDescribe) is"
switch integerToDescribe {
  case 2, 3, 5, 7, 11, 13, 17, 19:
    description += " a prime number, and also"
    fallthrough
default:
  description += " an integer."
}

print(description)

// "The number 5 is a prime number, and also an integer."
```

### Utilisation de tuple
```
let somePoint = (1, 1)
switch somePoint {
  case (0, 0):
    print("\(somePoint) is at the origin")
  case (_, 0):
    print("\(somePoint) is on the x-axis")
  case (0, _):
    print("\(somePoint) is on the y-axis")
  case (-2...2, -2...2):
    print("\(somePoint) is inside the box")
  default:
    print("\(somePoint) is outside of the box")
}
// "(1, 1) is inside the box"
```

### Value binding

```
let anotherPoint = (2, 0)
switch anotherPoint {
  case (let x, 0):
    print("on the x-axis with an x value of \(x)")
  case (0, let y):
    print("on the y-axis with a y value of \(y)")
  case let (x, y):
    print("somewhere else at (\(x), \(y))")
}
// Affiche "on the x-axis with an x value of 2"
```

### Where
```
let yetAnotherPoint = (1, -1)
switch yetAnotherPoint {
  case let (x, y) where x == y:
    print("(\(x), \(y)) is on the line x == y")
  case let (x, y) where x == -y:
    print("(\(x), \(y)) is on the line x == -y")
  case let (x, y):
    print("(\(x), \(y)) is just some arbitrary point")
}
// Affiche "(1, -1) is on the line x == -y"
```

## Guard
On procède à une évaluation d'une commande ou assignation, si elle retourne fausse, on va faire une opération:

```
func greet(person: [String: String]) {
  guard let name = person["name"] else {
    return
  }

  print("Hello \(name)!") 

  guard let location = person["location"] else {
    print("I hope the weather is nice near you.")
    return
  }

  print("I hope the weather is nice in \(location).")
  return 
}

greet(person: ["name": "John"])
// "Hello John!"
// "I hope the weather is nice near you."

greet(person: ["name": "Jane", "location": "Cupertino"])
// "Hello Jane!"
// "I hope the weather is nice in Cupertino."

```

## Fonctions
Les fonctions en Swift sont relativement simples, elles peuvent recevoir une multitude d'argument, le retour est spécifié après la flèche ->.

```
func greet(person: String) -> String {
  let greeting = "Hello, " + person + "!"
  return greeting
}
```

Pour appeler cette méthode, nous utilisons ceci:

```
print(greet(person: "Anna"))
// "Hello, Anna!"

print(greet(person: "Brian"))
// "Hello, Brian!"
```

Exemple de fonction un peu plus utile: 
```
func minMax(array: [Int]) -> (min: Int, max: Int)? {
  if array.isEmpty { return nil }
  var currentMin = array[0]
  var currentMax = array[0]
  for value in array[1..<array.count] {
    if value < currentMin {
      currentMin = value
    } else if value > currentMax {
      currentMax = value
    }
  }
  return (currentMin, currentMax)
}

if let bounds = minMax(array: [8, -6, 2, 109, 3, 71]) {
print("min is \(bounds.min) and max is \(bounds.max)")
}
// "min is -6 and max is 109"
```

Il est possible d'omettre des arguments pour une fonction lorsqu'elle est appelée:

func someFunction(_ firstParameterName: Int, secondParameterName: Int) {
  // In the function body, firstParameterName and secondParameterName
  // refer to the argument values for the first and second parameters.
}
someFunction(1, secondParameterName: 2)

### Fonction paramètres variables

```
func moyenneArithmetique(_ numbers: Double...) -> Double {
    var total: Double = 0

    for number in numbers {
        total += number
    }

    return total / Double(numbers.count)
}

moyenneArithmetique(1, 2, 3, 4, 5)
// retourne 3.0

moyenneArithmetique(3, 8.25, 18.75)
// retourns 10.0

```

Il est possible d'utiliser inout afin d'obtenir un argument de la méthode par référence (et non par valeur) alors, il serait possible de le modifier.

Le guard, vu précédemment, peut également être utilisé dans une fonction pour s'assurer qu'une valeur soit bien un "Int" même s'il provient par exemple d'une boîte de texte non-convertie en Int:

```
func buySomething(itemValueField: String, cardBalance: Int) -> Int {
  guard let itemValue = Int(itemValueField) else {
    print("error in item value")
    return cardBalance
  }
  let remainingBalance = cardBalance - itemValue
  return remainingBalance
}
print(buySomething(itemValueField: "10", cardBalance: 50))
print(buySomething(itemValueField: "blue", cardBalance: 50))
```

## Set

Il s'agit exactement d'une collection d'élément où l'ordre n'a aucune importance. On utilise d'ailleurs un Set à la place d'un Array lorsque l'ordre n'a pas d'importante. 

```

// letters est de type Set<Character> avec 0 items.
var letters = Set<Character>()

// letters now contains 1 value of type Character
letters.insert("a")

// letters is now an empty set, but is still of type Set<Character>
letters = []

var favoriteGenres: Set<String> = ["Rock", "Classical", "Hip hop"]

```
Même méthode disponible pour le Set que le array: isEmpty, count, remove, insert, contains
```

Pour itérer sur un set:

for genre in favoriteGenres {
  print("\(genre)")
}
// Classical
// Jazz
// Hip hop

```

Opération sur des Sets:

![](images/setVennDiagram_2x.png)

```
let oddDigits: Set = [1, 3, 5, 7, 9]
let evenDigits: Set = [0, 2, 4, 6, 8]
let singleDigitPrimeNumbers: Set = [2, 3, 5, 7]

oddDigits.union(evenDigits).sorted()
// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
oddDigits.intersection(evenDigits).sorted()
// []
oddDigits.subtracting(singleDigitPrimeNumbers).sorted()
// [1, 9]
oddDigits.symmetricDifference(singleDigitPrimeNumbers).sorted()
// [1, 2, 9]
```

![](images/setEulerDiagram_2x.png)

* a est le superSet de b, car a contient b.
* b est un subset de a car b est contenu dans a.
* b et c sont disjoints.

## Dictionnaires

Un dictionnaire store des clés de même type pointant vers des valeurs de même type. Chaque valeur est associée à une clé unique, qui est en réalité un identifiant dans le dictionnaire. Contrairement à l'array, les items d'un dictionnaire n'ont pas d'ordre.

```
var namesOfIntegers: [Int: String] = [:]

// namesOfIntegers is an empty [Int: String] dictionary
namesOfIntegers[16] = "sixteen"

// namesOfIntegers now contains 1 key-value pair
namesOfIntegers = [:]

// namesOfIntegers is once again an empty dictionary of type [Int: String]

var airports = ["YYZ": "Toronto Pearson", "DUB": "Dublin"]
print("The airports dictionary contains \(airports.count) items.")

// "The airports dictionary contains 2 items."

if airports.isEmpty {
  print("The airports dictionary is empty.")
} else {
  print("The airports dictionary isn't empty.")
}

// "The airports dictionary isn't empty."

// Pour ajouter un item dans le dictionnaire, il y aura 3 items:
airports["LHR"] = "London"

// Pour mettre à jour un item du dictionnaire,
airports["LHR"] = "London Heathrow"

Afin de mettre à jour une clé, on peut aussi utiliser la méthode updateValue

if let oldValue = airports.updateValue("Dublin Airport", forKey: "DUB") {
  print("The old value for DUB was \(oldValue).")
}
// "The old value for DUB was Dublin."

Pour tester la présence d'un objet dans le dictionnaire:

if let airportName = airports["DUB"] {
  print("The name of the airport is \(airportName).")
} else {
  print("That airport isn't in the airports dictionary.")
}
// "The name of the airport is Dublin Airport."

Pour retirer un élément d'un dictionnaire:

airports["APL"] = "Apple International"
airports["APL"] = nil

Sinon, une méthode existe également:

if let removedValue = airports.removeValue(forKey: "DUB") {
  print("The removed airport's name is \(removedValue).")
} else {
  print("The airports dictionary doesn't contain a value for DUB.")
}

// "The removed airport's name is Dublin Airport."
```
