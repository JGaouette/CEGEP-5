package com.example.black_jack

class DeckRepo {
    var client: API = Retrofit.initClient()

    suspend fun getDeck() = client.getDeck()
}