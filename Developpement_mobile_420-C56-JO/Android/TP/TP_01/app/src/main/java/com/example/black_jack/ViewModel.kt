package com.example.black_jack

import androidx.lifecycle.ViewModel
import androidx.lifecycle.liveData
import kotlinx.coroutines.Dispatchers

class ViewModel : ViewModel() {
    private val deckRepo = DeckRepo()
    private val cardRepo = CardRepo()

    private val playerHand = mutableListOf<Card>()
    private val dealerHand = mutableListOf<Card>()

    fun getDeck() = liveData(Dispatchers.IO) {
        val response = deckRepo.getDeck()
        emit(response)
    }

    fun drawCard(deckId: Int) = liveData(Dispatchers.IO) {
        val result = cardRepo.getCard(deckId)
        emit(result)
    }

    fun addPlayerCard(card: Card) {
        playerHand.add(card)
    }

    fun addDealerCard(card: Card) {
        dealerHand.add(card)
    }

    fun getPlayerHand() = playerHand
    fun getDealerHand() = dealerHand
}