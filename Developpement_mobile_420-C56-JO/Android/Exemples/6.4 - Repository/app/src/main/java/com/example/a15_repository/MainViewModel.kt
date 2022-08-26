package com.example.a15_repository

import androidx.lifecycle.ViewModel
import androidx.lifecycle.liveData
import kotlinx.coroutines.Dispatchers

class MainViewModel : ViewModel() {
    private val repository: TodoRepository = TodoRepository()

    val firstTodo = liveData(Dispatchers.IO) {
        val retrivedTodo = repository.getTodo(1)

        emit(retrivedTodo)
    }
}