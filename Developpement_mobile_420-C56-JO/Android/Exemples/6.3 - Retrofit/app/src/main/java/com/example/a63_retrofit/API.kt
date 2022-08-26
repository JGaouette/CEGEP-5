package com.example.a63_retrofit

import retrofit2.Call
import retrofit2.http.*


interface API {

    @GET("todos")
    fun getTodos(): Call<List<Todo?>?>?

    @GET("/todos")
    fun getTodosByUserId(@Query("userId") id: String): Call<List<Todo?>?>?

    @POST("/todos")
    fun addTodos(@Body todo : Todo) : Call<Todo>
}