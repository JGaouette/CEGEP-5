package com.example.a8_hockeyviewmodel

import androidx.lifecycle.LiveData
import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class Score(

    // Date for the
    @PrimaryKey val date : Long,
    @ColumnInfo(name="ScoreA", defaultValue = "0") val scoreA : Int,
    @ColumnInfo(name="ScoreB", defaultValue = "0") val scoreB : Int

    )