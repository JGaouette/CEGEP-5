package com.example.black_jack

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class Stats (
    @PrimaryKey val ID : Long,
    @ColumnInfo(name="Type") val type : String,
    @ColumnInfo(name="Number") val number : Int
)