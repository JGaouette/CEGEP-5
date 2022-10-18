package com.example.black_jack

import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.Retrofit

class Retrofit {
    companion object {
        fun initClient(): API {
            return Retrofit.Builder()
                .baseUrl("https://c56.drynish.synology.me/")
                .addConverterFactory(GsonConverterFactory.create())
                .build()
                .create(API::class.java)
        }
    }
}



