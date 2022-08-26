package com.example.a8_hockeyviewmodel

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class ScoreViewModel() : ViewModel() {

    private val _scoreA = MutableLiveData<Int>()
    private val _scoreB = MutableLiveData<Int>()

    init {
        _scoreA.value = 0
        _scoreB.value = 0
    }

    val scoreA: LiveData<Int> = _scoreA
    val scoreB: LiveData<Int> = _scoreB

    fun incrementScoreA() {
        _scoreA.value = _scoreA.value!! + 1
    }

    fun decrementScoreA() {
        if (_scoreA.value!! > 0) {
            _scoreA.value = _scoreA.value!! - 1
        }
    }

    fun incrementScoreB() {
        _scoreB.value = _scoreB.value!! + 1
    }

    fun decrementScoreB() {
        if (_scoreB.value!! > 0) {
            _scoreB.value = _scoreB.value!! - 1
        }
    }

}