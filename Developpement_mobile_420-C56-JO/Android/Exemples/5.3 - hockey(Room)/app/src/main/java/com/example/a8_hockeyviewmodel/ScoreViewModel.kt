package com.example.a8_hockeyviewmodel

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.launch

class ScoreViewModel(application: Application) : AndroidViewModel(application) {

    private val scoreDAO = ScoreDatabase.getDatabase(application)!!.scoreDAO()

    val scoreA : LiveData<Int?> = scoreDAO.getA()
    val scoreB : LiveData<Int?> = scoreDAO.getB()


    fun incrementScoreA() {
        var score = Score(System.currentTimeMillis(), scoreA?.value?.plus(1) ?: 1, scoreB?.value ?: 0 )
        updateScore(score)
    }

    fun incrementScoreB() {
        var score = Score(System.currentTimeMillis(), scoreA?.value ?: 0, scoreB?.value?.plus(1) ?: 1)
        updateScore(score)
    }

    fun deleteLast()  = viewModelScope.launch {
        scoreDAO.deleteLastScore()
    }


    fun updateScore(score : Score) = viewModelScope.launch {
        scoreDAO.insertNewScore(score)
    }

}