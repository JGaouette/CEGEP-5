package com.example.simon

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class ViewModel : ViewModel() {
    val goodSequence = MutableLiveData<List<Int>>()
    private val userSequence = MutableLiveData<List<Int>>()
    val turn = MutableLiveData<Int>()
    private val score = MutableLiveData<Int>()
    var highScore = MutableLiveData<Int>()

    init {
        goodSequence.value = listOf()
        userSequence.value = listOf()
        turn.value = 0
        score.value = 0
        highScore.value = 0
    }

    fun getTurn() = turn as LiveData<Int>
    fun getScore() = score as LiveData<Int>
    fun getHighScore() = highScore as LiveData<Int>
    fun getGoodSequence() = goodSequence as LiveData<List<Int>>
    fun getUserSequence() = userSequence as LiveData<List<Int>>


    fun addScore(){
        score.value = score.value?.plus(1)
    }

    fun setHighScore(){
        highScore.value = score.value
    }

    fun getGoodSize() : Int? {
        return goodSequence.value?.size
    }

    fun addGoodSequence(){
        val rand = (0..3).random()
        goodSequence.value = goodSequence.value?.plus(rand)
        userSequence.value = listOf()
    }

    fun addUserSequence(nb: Int) {
        userSequence.value = userSequence.value?.plus(nb)
    }



    fun reset(){
        goodSequence.value = listOf()
        userSequence.value = listOf()
        turn.value = 0
        score.value = 0
    }



}