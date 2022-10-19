package com.example.black_jack

data class Card (
    val rank: String,
    val suit: String,
    var hidden: Boolean = false
)