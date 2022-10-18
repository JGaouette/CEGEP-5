package com.example.black_jack

import retrofit2.http.GET
import retrofit2.http.Path

interface API {
    @GET("/getDeck/")
    suspend fun getDeck(): Deck

    @GET("/getCard/{ID}")
    suspend fun getCard(@Path(value= "ID") int: Int ):Card
}