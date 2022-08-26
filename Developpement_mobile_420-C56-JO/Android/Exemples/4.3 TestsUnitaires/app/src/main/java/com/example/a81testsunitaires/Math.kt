package com.example.a81testsunitaires

class Math (val String_chiffre1: String, val String_chiffre2: String){
    var chiffre1 = 0
    var chiffre2 = 0

    init {
        try {
            chiffre1 = String_chiffre1.toInt()
            chiffre2 = String_chiffre2.toInt()
        } catch (e: NumberFormatException) {
            throw java.lang.NumberFormatException()
        }
    }

    fun PGCD() : Int {
        var pgcd = 1
        for (j in 1..chiffre2) {
            if (chiffre1.rem(j) == 0 && chiffre2.rem(j) == 0)
                pgcd = j
        }
        return pgcd
    }
}