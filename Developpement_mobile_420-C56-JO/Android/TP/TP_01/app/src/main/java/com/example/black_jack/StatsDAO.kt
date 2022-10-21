package com.example.black_jack

import androidx.lifecycle.LiveData
import androidx.room.*

@Dao
interface StatsDAO {
    @Query("SELECT * FROM Stats")
    fun getStats(): LiveData<List<Stats>>

    @Query("SELECT Number FROM Stats WHERE Type = :type")
    fun getStatNumber(type: String) : Int

    @Query("UPDATE Stats SET Number = :number WHERE Type = :type")
    fun updateStatNumber(type: String, number: Int)

    fun removeOneStat(type: String) = updateStatNumber(type, getStatNumber(type) - 1)

    @Query("SELECT SUM(Number) FROM Stats")
    fun getRemainingCards(): Int

    @Insert
    fun insertStats(stats: Stats)

    @Query("DELETE FROM Stats")
    fun resetStats()
}