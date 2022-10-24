package com.example.black_jack

import android.app.Application
import androidx.lifecycle.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class MainViewModel(application: Application) : AndroidViewModel(application) {
    private val repo = Repository()

    private val playerHand = MutableLiveData<List<Card>>()
    private val dealerHand = MutableLiveData<List<Card>>()

    private val betIsVisible = MutableLiveData<Boolean>()
    private val statsIsVisible = MutableLiveData<Boolean>()

    private val statsDAO = StatsDatabase.getDatabase(application).statsDAO()
    private val remainingCards = MutableLiveData<Int>()

    init {
        playerHand.value = listOf()
        dealerHand.value = listOf()
    }

    /**** Game ****/

    fun getPlayerCardCount() = playerHand.value?.size ?: 0
    fun getDealerCardCount() = playerHand.value?.size ?: 0

    fun getPlayerHand() = playerHand as LiveData<List<Card>>
    fun getDealerHand() = dealerHand as LiveData<List<Card>>

    fun statsIsVisible() = statsIsVisible as LiveData<Boolean>

    fun setStatsVisible(isVisible: Boolean) {statsIsVisible.value = isVisible }

    fun getDeck() = liveData(Dispatchers.IO) {
        val response = repo.getDeck()
        emit(response)
    }

    fun drawCard(deckId: Int) = liveData(Dispatchers.IO) {
        val result = repo.getCard(deckId)

        withContext(Dispatchers.Main) {
            remainingCards.value = statsDAO.getRemainingCards()
        }

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

    /**** Database ****/

    fun initDatabase() = viewModelScope.launch {
        statsDAO.resetStats()

        statsDAO.insertStats(Stats(1, "As", 28))
        statsDAO.insertStats(Stats(2, "10", 112))
        statsDAO.insertStats(Stats(3, "9", 28))
        statsDAO.insertStats(Stats(4, "8", 28))
        statsDAO.insertStats(Stats(5, "7", 28))
        statsDAO.insertStats(Stats(6, "6", 28))
        statsDAO.insertStats(Stats(7, "5", 28))
        statsDAO.insertStats(Stats(8, "4", 28))
        statsDAO.insertStats(Stats(9, "3", 28))
        statsDAO.insertStats(Stats(10, "2", 28))
    }

    fun getStatNumber(type: String) = statsDAO.getStatNumber(type)

    fun getRemainingCards() = remainingCards as LiveData<Int>

    fun removeOneStat(rank: String) = viewModelScope.launch {
        if (rank == "Roi" || rank == "Dame" || rank == "Valet") {
            statsDAO.removeOneStat("10")
        } else {
            statsDAO.removeOneStat(rank)
        }
    }

    /**** Bank ****/
    val bank = MutableLiveData<Int>()
    val bet = MutableLiveData<Int>()
    var inGame = MutableLiveData<Boolean>()

    fun initGame() {
        bank.value = 100
        bet.value = 0
        inGame.value = false
    }

    fun indebtedForLife() {
        bank.value = bank.value?.plus(100)
    }

    fun sendBet(value: Int) {
        bet.value = value
    }
}