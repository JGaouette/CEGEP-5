package com.example.a8_hockeyviewmodel

import androidx.lifecycle.LiveData
import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.Query

@Dao
interface ScoreDAO{
    @Query("SELECT ScoreA FROM score ORDER BY Date DESC LIMIT 1")
    fun getA(): LiveData<Int?>

    @Query("SELECT ScoreB FROM score ORDER BY Date DESC LIMIT 1")
    fun getB(): LiveData<Int?>

    @Insert
    suspend fun insertNewScore(score: Score)

    @Query("DELETE FROM Score WHERE Date = (SELECT MAX(Date) FROM Score)")
    suspend fun deleteLastScore()
}