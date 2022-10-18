package com.example.black_jack

class CardRepo {
    var client: API = Retrofit.initClient()
    suspend fun getCard(deckID: Int) = client.getCard(deckID)
}