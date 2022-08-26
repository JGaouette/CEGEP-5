fun main() {
    var character : Character? = null

    var isGood = false
    while(!isGood){
        println("Choose your classe \n1: Warrior \n2: Mage \n" +
                "3: Cleric")

        when (readLine()) {
            "1" -> {
                character = Warrior()
                isGood = true
            }
            "2" -> {
                character = Mage()
                isGood = true
            }
            "3" -> {
                character = Cleric()
                isGood = true
            }
            else -> {
                println("This class doesn't exist \n")
            }
        }
    }


    println("Class: " + character!!.javaClass.name + "   Health: " + character.health + "/" + character.maxHealth)
}

abstract class Entity {
    abstract var attack: Int
    abstract var defense: Int
    abstract var health: Int
    abstract var maxDamage: Int

    open fun attack(against : Entity) {
        var difficulty = this.attack - against.defense
        var touch = (0..20).random()

        if (touch >= difficulty){
            against.health -= (1..this.maxDamage).random()
        }
    }
}

class Monster : Entity() {
    override var attack = (15..20).random()
    override var defense = (2..8).random()
    override var health = (3..10).random()
    override var maxDamage = 5
}

abstract class Character : Entity()  {
    abstract var maxHealth : Int


    open fun special(){}

    open fun flee(against : Entity) {
        against.attack(this)
        this.health = this.maxHealth
    }
}

class Warrior : Character() {
    override var attack = 16
    override var defense = 2
    override var maxHealth = 10
    override var health = 10
    override var maxDamage = 8

    override fun special(){}
}

class Mage : Character() {
    override var attack = 19
    override var defense = 8
    override var maxHealth = 5
    override var health = 5
    override var maxDamage = 4

    override fun special(){}
}

class Cleric : Character() {
    override var attack = 17
    override var defense = 4
    override var maxHealth = 8
    override var health = 8
    override var maxDamage = 6

    override fun special(){}
}