package com.example.a15_repository

// Correspondant à https://jsonplaceholder.typicode.com/todos/1

data class Todo(
    val id: Int = 0,
    val title: String = "",
    val completed: Boolean = false
)
