package com.example.black_jack

import android.app.Application
import androidx.lifecycle.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

class MainViewModel(application: Application) : AndroidViewModel(application) {
    private val repo = Repository()

    private val playerHand = MutableLiveData<List<Card>>()
    private val dealerHand = MutableLiveData<List<Card>>()

    private val betIsVisible = MutableLiveData<Boolean>()
    private val statsIsVisible = MutableLiveData<Boolean>()

    private val statsDAO = StatsDatabase.getDatabase(application).statsDAO()

    init {
        playerHand.value = listOf()
        dealerHand.value = listOf()
    }

    fun getPlayerCardCount() = playerHand.value?.size ?: 0
    fun getDealerCardCount() = playerHand.value?.size ?: 0

    fun getPlayerHand() = playerHand as LiveData<List<Card>>
    fun getDealerHand() = dealerHand as LiveData<List<Card>>

    fun betIsVisible() = betIsVisible as LiveData<Boolean>
    fun statsIsVisible() = statsIsVisible as LiveData<Boolean>

    fun setBetVisibile(isVisible: Boolean) { betIsVisible.value = isVisible }

    fun setStatsVisible(isVisible: Boolean) {statsIsVisible.value = isVisible }

    fun getDeck() = liveData(Dispatchers.IO) {
        val response = repo.getDeck()
        emit(response)
    }

    fun drawCard(deckId: Int) = liveData(Dispatchers.IO) {
        val result = repo.getCard(deckId)
        removeStats(result.rank)
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

    val stats : LiveData<List<Stats>> = statsDAO.getStats()

    fun resetStats() = viewModelScope.launch {
        statsDAO.resetStats(listOf(
            Stats(1, "As", 28),
            Stats(2, "10", 112),
            Stats(3, "2", 28),
            Stats(4, "3", 28),
            Stats(5, "4", 28),
            Stats(6, "5", 28),
            Stats(7, "6", 28),
            Stats(8, "7", 28),
            Stats(9, "8", 28),
            Stats(10, "9", 28))
        )
    }

    private fun removeStats(type: String) {
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
    }

    fun getAllStats() : List<Stats> {
        return statsDAO.getStats().value ?: listOf()
    }
}