# Function (suite)

## Closure

Un closure est comme une fonction inline n'ayant aucun nom:

```
var numbersArray = [2, 4, 6, 7]
let myClosure = { (number: Int) -> Int in
  let result = number * number
  return result
}

let mappedNumbers = numbersArray.map(myClosure)
print(mappedNumbers)

// [4, 16, 36, 49]
```

ou plus simplement, lorsque les types sont connus comme dans cet exemple (vu qu'on connaît sur quoi on joue):

```
var testNumbers = [2, 4, 6, 7]
let mappedTestNumbers = testNumbers.map({
  number in number * number })
print(mappedTestNumbers)
```

Quand la closure est le seul argument de la fonction, on peut omettre les paranthèses:

```
var testNumbers = [2, 4, 6, 7]
let mappedTestNumbers = testNumbers.map {
  number in number * number }
print(mappedTestNumbers)
```

# Class

## Déclaration

```
class Animal {
  var name: String = ""
  var sound: String = ""
  var numberOfLegs: Int = 0
  var breathesOxygen: Bool = true
  func makeSound() {
    print(self.sound)
  }
}

let cat = Animal()

cat.name="Alfred"
cat.sound="Gazouiller"
cat.numberOfLegs=4
cat.breathesOxygen=false


print(cat.name)
print(cat.sound)
print(cat.numberOfLegs)
print(cat.breathesOxygen)
cat.makeSound()
```


## Constructeur... init()

Le constructeur est défini par la méthode init et s'assure que toutes les propriétés sont valides lorsque la classe est est créée:

```
init(name: String, sound: String, numberOfLegs: Int, breathesOxygen: Bool) {
  self.name = name
  self.sound = sound
  self.numberOfLegs = numberOfLegs
  self.breathesOxygen = breathesOxygen
}

let cat = Animal(name: "Cat", sound: "Mew", numberOfLegs:4, breathesOxygen: true)
```

## Héritage

class Mammal: Animal {
  let hasFurOrHair: Bool = true
}

let cat = Mammal(name: "Cat", sound: "Mew", numberOfLegs:4, breathesOxygen: true)

## Override

Le override permet de redéfinir une méthode spécifiée par le parent mais que vous désirez changer son comportement

```
class Animal {
...  
func description() -> String{
    return "name: \(self.name) sound: \(self.sound) numberOfLegs: \(self.numberOfLegs) breathesOxygen:
    \(self.breathesOxygen)"
  }
}

class Mammal:Animal {
...
override func description() -> String {
    return super.description() + " hasFurOrHair: \(self.hasFurOrHair) "
}

```

Veuillez noter la présence du super comme en Kotlin afin de faire appel à la méthode parent de Mammal.

# Struct

## Déclaration

```
struct Reptile {
  var name: String
  var sound: String
  var numberOfLegs: Int
  var breathesOxygen: Bool
  let hasFurOrHair: Bool = false
  
  func makeSound() {
    print(sound)
  }
  
  func description() -> String {
    return "Structure: Reptile name: \(self.name) sound: \(self.sound) numberOfLegs: \(self.numberOfLegs)
      breathesOxygen: \(self.breathesOxygen) hasFurOrHair: \(self.hasFurOrHair)"
  }
}
```

Quasiment identique à la classe Animal déclarée plus haut.

## Instanciation

var snake = Reptile(name: "Snake", sound: "Hiss",numberOfLegs: 0, breathesOxygen: true)
print(snake.description())
snake.makeSound()

À noter qu'il n'est pas nécessaire dans une structure de créer une méthode init.

Deux distinctions principales entre classe et struct:

* Structure ne peuvent pas hériter
* Class est de type référence, struct de type valeur
* Différence entre référence et valeur

```
struct SampleValueType {
  var sampleProperty = 10
}

var a = SampleValueType()
var b = a

b.sampleProperty = 20

print(a.sampleProperty)
print(b.sampleProperty)
```

vs
```
class SampleReferenceType {
  var sampleProperty = 10
}
var c = SampleReferenceType()
var d = c
c.sampleProperty = 20
print(c.sampleProperty)
print(d.sampleProperty)
```

Dans le premier cas, b est une copie donc a n'est pas modifié lors de la modification de b.sampleProperty. Ce qui n'est pas le cas pour la référence vu que c et d pointent au même objet en mémoire. De façon générale, en swift, les struct sont recommandées à moins que vous nécessitez l'utilisation de l'héritage.

# Énumération

## Déclaration

```
enum TrafficLight {
  case red
  case yellow
  case green
  
  func trafficLightDescription() -> String {
    switch self {
      case .red:
        return "red"
      case .yellow:
        return "yellow"
      default:
        return "green"
    }
  }
}

var trafficLight = TrafficLight.red
print(trafficLight.trafficLightDescription())
```

# Protocol

Un protocol est similaire à une interface en Java. Il s'agit d'un modèle de propriétés et de méthodes qu'une classe, qu'une struct ou qu'un enum doivent posséder.

Par exemple:

protocol CalorieCountProtocol {
  var calories: Int { get }
  func description() -> String
}

Quelques petites précisions, on voit que le protocol CalorieCountProtocol a deux objets, l'obligation d'avoir une propriété accessible en get uniquement (readonly) nommé calories et une méthode description.

Soit les 3 objets suivants:

```
class Burger {
}

struct Fries {
}

enum Sauce {
  case chili
  case tomato
}
```

Ils doivent être modifiés pour respecter le protocol CalorieCountProtocol:

```
class Burger : CalorieCountProtocol {
  let calories = 800
  func description() -> String {
    return "This burger has \(calories) calories"
  }
}

struct Fries : CalorieCountProtocol {
  let calories = 500
  func description() -> String {
    return "These fries have \(calories) calories"
  }
}

```
On aurait pu modifier la Sauce de la même façon, mais regardons une nouvelle fonctionnalité.

# Extension
L'extension permet d'ajouter des méthodes et propriétés à une classe existante:

```
class ExistingType {
  property1
  method1()
}
extension ExistingType : ProtocolName {
  property2
  method2()
}
```

Il serait même possible d'ajouter des propriétés et des méthodes aux objets de Apple

```
extension Sauce : CalorieCountProtocol {
  var calories : Int {
    switch self {
      case .chili:
        return 20
      case .tomato:
        return 15
    }
  }
  func description() -> String {
    return "This sauce has \(calories) calories"
  }
}
```

## Utilisation

```
let burger = Burger()
let fries = Fries()
let sauce = Sauce.tomato

let foodArray : [CalorieCountProtocol] = [burger, fries, sauce]
var totalCalories = 0
for food in foodArray {
  totalCalories += food.calories
}
print(totalCalories)
```
