package com.example.a15_repository

class TodoRepository {
    var client: TodoAPI = RetrofitClient.initClient()

    suspend fun getTodo(id: Int) = client.getTodo(id)
}