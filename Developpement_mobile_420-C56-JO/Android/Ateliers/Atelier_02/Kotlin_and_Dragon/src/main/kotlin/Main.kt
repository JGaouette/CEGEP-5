fun main() {
    var character : Character? = null
    var inFight = true

    while(character == null){
        println("Choose your class \n1: Warrior \n2: Mage \n" +
                "3: Cleric")

        character = when (readLine()) {
            "1" ->  Warrior()
            "2" -> Mage()
            "3" ->  Cleric()
            else -> null
        }
    }

    while(inFight){
        val monster = Monster()

        while (character.health > 0 && monster.health > 0){
            println("Class: " + character.javaClass.name + "             Class: " + monster.javaClass.name)
            println("Health: " + character.health + "/" + character.maxHealth + "      VS      Health: " + monster.health + "/" + monster.maxHealth)
            println("Attack: " + character.attack + "                 Attack: " + monster.attack)
            println("Defense: " + character.defense + "                Defense: " + monster.defense)
            println("")

            var action : String? = null
            while (action == null){
                if(character.cooldown > 0)
                    println("1: Attack  |  2: Special Attack (In " + character.cooldown + " turns )  |  3: Flee like a fool")
                else
                    println("1: Attack  |  2: Special Attack (Ready)  |  3: Flee like a fool")

                action = readLine()

                when (action) {
                    "1" -> character.attack(monster)
                    "2" -> character.special(monster)
                    "3" -> character.flee(monster)
                    else -> action = null
                }
                println()
            }

            if(monster.health > 0) monster.attack(character)

            if(character.health <= 0 || monster.health <= 0){
                if(character.health <= 0){
                    println("You are DEAD! Shame on you and your family")
                }
                if(monster.health <= 0){
                    println("Good job, you have slain the enemy!")
                }

                println("Do you want to make an other fight? \"Yes\" to continue, other stuff to be a coward")
                when (readLine()) {
                    "Yes" -> character.levelUp()
                    else-> inFight = false
                }
            }
        }
    }
}

abstract class Entity {
    abstract var attack: Int
    abstract var defense: Int
    abstract var maxHealth : Int
    abstract var health: Int
    abstract var minDamage: Int
    abstract var maxDamage: Int

    open fun attack(against : Entity) {
        val difficulty = this.attack - against.defense
        val touch = (0..20).random()

        if (touch >= difficulty){
            against.getHit((minDamage..this.maxDamage).random())
        }
    }

    open fun getHit(damage : Int) {
        health -= damage
    }
}

class Monster : Entity() {
    override var attack = (15..20).random()
    override var defense = (2..8).random()
    override var maxHealth = (3..10).random()
    override var health = maxHealth
    override var minDamage = 1
    override var maxDamage = 5
}

abstract class Character : Entity()  {
    open var cooldown = 3

    override fun attack(against : Entity) {
        val difficulty = this.attack - against.defense
        val touch = (0..20).random()

        if (touch >= difficulty)
            against.getHit((minDamage..this.maxDamage).random())

        if(cooldown > 0) cooldown--
    }
    open fun special(against : Entity){}

    open fun flee(against : Entity) {
        against.attack(this)
        heal(maxHealth)
    }

    open fun heal(hp : Int){
        this.health += hp
        if(this.health > this.maxHealth) this.health = this.maxHealth
    }

    open fun levelUp(){
        this.attack += 1
        this.defense += 1
        this.maxHealth += 1
        this.health += 1
        this.minDamage += 1
        this.maxDamage += 1
    }
}

class Warrior : Character() {
    override var attack = 16
    override var defense = 2
    override var maxHealth = 10
    override var health = 10
    override var minDamage = 1
    override var maxDamage = 8

    override fun special(against : Entity){
        against.getHit((minDamage..this.maxDamage).random())
        cooldown += 2
    }
}

class Mage : Character() {
    override var attack = 19
    override var defense = 8
    override var maxHealth = 5
    override var health = 5
    override var minDamage = 1
    override var maxDamage = 4

    override fun special(against : Entity){
        against.getHit((4..10).random())
        cooldown += 2
    }
}

class Cleric : Character() {
    override var attack = 17
    override var defense = 4
    override var maxHealth = 8
    override var health = 8
    override var minDamage = 1
    override var maxDamage = 6

    override fun special(against : Entity){
        this.heal((2..6).random())
        cooldown += 2
    }
}