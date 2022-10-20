package com.example.black_jack

class Repository {
    var client: API = Retrofit.initClient()

    suspend fun getCard(deckID: Int) = client.getCard(deckID)
    suspend fun getDeck() = client.getDeck()
}