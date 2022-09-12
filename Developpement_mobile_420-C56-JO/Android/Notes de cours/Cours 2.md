# Classes

```
class Animal {

  var couleur = ""
  var food = ""
  var habitat = ""

  fun crie() {

  }
  
  fun eat() {

  }
}
```

**Fait**

* Il n'y a pas de constructeur, le compilateur en a ajouté un lui-même, nommé Animal()

## get / set

Le langage va créer les getter et setter automatiquement, mais vous pouvez toujours redéfinir leur comportement

```
  var nbrPattes = 0
  get() = field
  
  set(value) {
      field = value 
  }
```

https://pl.kotl.in/EqRxAkUjY

## Constructeur

Le constructeur se définit en paranthèse après le nom de la classe. Il va initier les variables situées après et assigner les getter et setter automatiquement.

```
class Auto(var marque: String, var modele: String, var couleur: Int) {

}
```



## Héritage   


Pour hériter, il faut transformer cette classe et l'assigner comme étant open.

```
open class Animal {

  open var couleur = ""
  open var food = ""
  open var habitat = ""

  open fun crie() {

  }
  
  open fun mange() {

  }

  open fun dort() {
    println("Je dors")
  }
}
```

Lorsqu'on veut hériter:

```
class Hippo : Animal() {
  override var couleur = "gris"
  override var food = "herbe"
  override var habitat = "eau des lacs africains"

  override fun crie() {
    println("Il émet des mugissements")
  }

  override fun mange() {
    println("L'hippopotame mange de $food")
  }

}
```

https://pl.kotl.in/yUjinFQ-g

**Fait**
* Vous pouvez déclarer une propriété comme étant final afin d'éviter qu'une propriété soit override.
* Les appels aux méthodes vont du plus précis au moins précis. Donc si vous appelez une méthode qui n'est pas définit dans l'enfant, mais qui est définit dans le parent, c'est celle du parent qui se fera appelée.

Le compilateur est assez brillant pour se rendre compte que si vous créez une liste d'Animal, par exemple un chien et un hippo, il va créer un arrayList<Animal>

```
var animaux = listOf(Hippo(), Chien())
    
for (animal in animaux)
 	animal.crie()
```

https://pl.kotl.in/zQm7uMGtH

** FAIT **

* Tester si une variable est d'un type avec la méthode **IS**, si une classe est dérivée d'une autre, par exemple Hippo IS a animal.

# Abstraction

Améliorons le code, il est possible dans la vraie vie de voir un hippo ou un chien, mais il est impossible de voir un "Animal" se promener, enfin vous comprenez.

On pourrait donc modifier notre code pour éviter qu'un utilisateur décide d'instancier un Animal

https://pl.kotl.in/V7gyVbqDX

** Fait **
* La méthode *dort()* doit restée présente et ne pas être abstraite car nous ne l'avons pas redéfinie partout.
* Le compilateur n'accepte pas que vous commenciez à écrire du code pour une fonction abstraite.
* Si une fonction ou une propriété est abstraite, toute la classe doit le devenir.
* Pour ce qui est des classes concrètes, vous devrez implémenter toutes les méthodes et propriétés abstraites que les classes abstraites desquelles vous dérivez. Si C dérive de B et que B dérive de A. B pourrait définir les méthodes abstraites de A, même si elle même est abstraite.

# Interface

Si vous désirez implémenter un même comportement entre deux classes qui n'ont aucun lien entre elle dans la hiérarchie, vous devez utiliser une interface. Par exemple dans notre cas, déplace() qui pourrait être rattachée à une certaine vitesse de déplacement. Cependant, puisque les animaux peuvent avoir une vitesse de déplacement, tout comme les voitures... nous allons donc offrir une interface 

https://pl.kotl.in/O83-J4U7C

## Comment savoir si l'on doit faire une classe, une classe enfant, une classe abstraite ou une interface?

* Faire une classe sans classe parent lorsqu'elle n'est pas du type parent. Par exemple, une auto n'est pas un animal.
* Faire une sous-classe lorsqu'elle doit héritée d'une classe parent quand vous devez avoir une classe plus spécifique et que vous devez modifié ou ajouter des nouveaux comportements
* Faire une classe abstraite quand vous souhaitez définir un modèle pour un groupe de classe, elle peut être utilisée pour être certain lorsque vous voulez qu'une classe ne peut être instanciéee.
* Faire une interface quand vous voulez que plusieurs classes puissent partager un comportement peu importe où elles sont situées dans la hiérarchie de classe.

Vous pouvez faire des petits tours de passes passes avec les interfaces:

```
var listDeplace = listOf(Chien(), Voiture())
for (element in listDeplace)
 	element.deplace()
  if (element is Animal)
    element.mange()
```

https://pl.kotl.in/1839etpyg

# Any

Chaque classe hérite de Any, même si vous ne le spécifier par

```
class MyClass {

}
```

est en réalité

```
class MyClass: Any {


}
```

## Pourquoi ?

* Ça permet de s'assurer que toutes les classes ont un minimum de comportement commun, comme par exemple la fonction equals() qui permet de vérifier si deux classes sont identiques.

* Ça permet d'exécuter du polymorphisme avec un ensemble d'objet même si rien ne semble les reliés:

```
val monTableau = arrayOf(Baton(), Orc(), Piano())
```

Le compileur va déterminer que la classe Any est celle qui unit les 3, va donc créer un tableau de type Any: Array<Any>.

### equals(any: Any): Boolean

Donc c'est une méthode qui permet de recevoir un objet de type Any, que vous pourriez caster en un autre objet en utilisant la méthode IS (testé) ou AS (forcé).

Par défaut, il compare si les deux objets:
* l'objet sur lequel on appelle la méthode 
* l'objet passé en paramètre
* ont la même référence, si c'est le cas: return true, sinon return false.

C'est cette méthode qui est appelée lorsqu'on utilise le ==.

### hashCode(): Int

Retourne un hash de la classe. Peut être utilisé par une structure pour stocker et retrouver les valeurs plus efficacement.

### toString(): String

Retourne une String qui représente l'objet.

# Data class

Bien que l'on pourrait override la méthode equals pour vérifier des conditions précises (si deux propriétés sont équivalentes, la classe est identique). Les développeurs kotlin ont créé un nouvel objet qui va simplifier la comparaison. Si une classe sert uniquement à stocker du contenu, vous pourriez utiliser le data class.

```
data class Auto (
  var couleur : String,
  var marque : String,
  var modèle : String ){}

fun main(){
	var bolt = Auto("jaune", "chevrolet", "bolt")
    var equinox = Auto("jaune", "chevrolet", "equinox")
    var bolt2 = Auto("jaune", "chevrolet", "bolt")
    
    if (equinox == bolt2) println("bonjour")
}
```

https://pl.kotl.in/sQ3ZvgKHU

Une data class n'utilise que les valeurs des propriétés pour vérifier que deux objets sont équivalents.

De plus, deux objets identiques vont retourner deux hashCode() identiques.

Finalement, si vous voulez vous assurez que la référence est la même entre deux objets, vous pouvez toujours utiliser le === lors de la comparaison (identité).

https://pl.kotl.in/YHJ_w6HT0