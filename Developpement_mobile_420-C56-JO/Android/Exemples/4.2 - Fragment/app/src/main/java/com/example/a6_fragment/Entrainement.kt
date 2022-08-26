package com.example.a6_fragment

data class Entrainement(val name:String, val description :String , val link: String)

val Entrainements = arrayOf(
    Entrainement(
        "Karaté Cardio",
        "Entraînement pour ne plus être fatigué mort en faisant du Karaté",
        "https://www.youtube.com/watch?v=pw9EnKA5Kzc"
    ),
    Entrainement(
        "Spinning",
        "Entraînement pour courrir 1 km en moins de 20 mins",
        "https://www.youtube.com/watch?v=4Hl1WAGKjMc&t=417s"
    ),
    Entrainement(
        "Puissant pour la maison",
        "Entraînement optimal pour l'ensemble du corps (pour notre côté féminin)",
        "https://www.youtube.com/watch?v=KWWeny18yWU"
    ),
    Entrainement(
        "DOUBLER SES PECTORAUX avec SEULEMENT 1 EXERCICE",
        "Entraînement pour avoir des pecs de dieu.",
        "https://www.youtube.com/watch?v=9vn9xnQVvdo"
    ),
    Entrainement(
        "ENTRAINEMENT POUR BRULER LES GRAISSES !!",
        "Entraînement sur les jambes pour pas avoir l'air de Chest Bras.",
        "https://www.youtube.com/watch?v=eEP6earF3Og"
    )
)