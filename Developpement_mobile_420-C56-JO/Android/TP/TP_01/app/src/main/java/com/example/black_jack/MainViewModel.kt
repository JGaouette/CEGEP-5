package com.example.black_jack

import android.app.Application
import androidx.lifecycle.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

class MainViewModel(application: Application) : AndroidViewModel(application) {
    private val deckRepo = DeckRepo()
    private val cardRepo = CardRepo()

    private val playerHand = MutableLiveData<List<Card>>()
    private val dealerHand = MutableLiveData<List<Card>>()

    init {
        playerHand.value = listOf()
        dealerHand.value = listOf()
    }

    fun getPlayerCardCount() = playerHand.value?.size ?: 0
    fun getDealerCardCount() = playerHand.value?.size ?: 0

    fun getPlayerHand() = playerHand as LiveData<List<Card>>
    fun getDealerHand() = dealerHand as LiveData<List<Card>>

    fun getDeck() = liveData(Dispatchers.IO) {
        val response = deckRepo.getDeck()
        emit(response)
    }

    fun drawCard(deckId: Int) = liveData(Dispatchers.IO) {
        val result = cardRepo.getCard(deckId)
        emit(result)
    }

    fun addPlayerCard(card: Card) {
        playerHand.value = playerHand.value?.plus(card)
    }

    fun addDealerCard(card: Card) {
        dealerHand.value = dealerHand.value?.plus(card)
    }

    fun getPlayerValue(): Int {
        var value = 0

        for (card in playerHand.value!!) {
            if (card.hidden) continue
            value += try {
                card.rank.toInt()
            } catch (e: NumberFormatException) {
                when (card.rank) {
                    "As" -> 11
                    else -> 10
                }
            }
            if (value > 21 && card.rank == "As") value -= 10
        }
        return value
    }

    fun getDealerValue(): Int {
        var value = 0

        for (card in dealerHand.value!!) {
            if (card.hidden) continue
            value += try {
                card.rank.toInt()
            } catch (e: NumberFormatException) {
                when (card.rank) {
                    "As" -> 11
                    else -> 10
                }
            }
            if (value > 21 && card.rank == "As") value -= 10
        }
        return value
    }

    fun resetHands() {
        playerHand.value = listOf()
        dealerHand.value = listOf()
    }
/*
    private val statsDAO = StatsDatabase.getDatabase(application).statsDAO()

    val stats : LiveData<List<Stats>> = statsDAO.getStats()

    //Remove one number of the chosen type of Stats from the database
    fun removeStats(type: String) {
        viewModelScope.launch {
            val stats = statsDAO.getStats().value
            if (stats != null) {
                for (stat in stats) {
                    if (stat.type == type) {
                        if (stat.number > 0) {
                            statsDAO.updateStats(Stats(stat.ID, stat.type, stat.number - 1))
                        }
                        break
                    }
                }
            }
        }
    }*/
}