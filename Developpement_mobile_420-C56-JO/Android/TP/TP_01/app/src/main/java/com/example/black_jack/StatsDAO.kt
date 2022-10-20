package com.example.black_jack

import androidx.lifecycle.LiveData
import androidx.room.*

@Dao
interface StatsDAO {
    @Query("SELECT * FROM Stats")
    fun getStats(): LiveData<List<Stats>>

    @Update
    fun updateStats(stats: Stats)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun resetStats(stats: List<Stats>)
}