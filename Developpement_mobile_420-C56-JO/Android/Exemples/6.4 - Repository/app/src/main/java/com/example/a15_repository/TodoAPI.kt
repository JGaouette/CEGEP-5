package com.example.a15_repository

import retrofit2.Call
import retrofit2.http.GET
import retrofit2.http.Path

interface TodoAPI {
    @GET("/todos/{id}")
    suspend fun getTodo(@Path(value = "id") todoId: Int): Todo
}