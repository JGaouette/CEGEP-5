package com.example.a8_hockeyviewmodel

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = [Score::class], version = 2)
abstract class ScoreDatabase : RoomDatabase(){
    abstract fun scoreDAO() : ScoreDAO

    companion object {

        @Volatile private var instance: ScoreDatabase? = null

        fun getDatabase(context: Context): ScoreDatabase? {
            return instance ?: synchronized(this) {
                instance ?: Room.databaseBuilder(
                    context.applicationContext,
                    ScoreDatabase::class.java, "scoreDatabase"
                )
                    .fallbackToDestructiveMigration()
                    .build()
            }
        }
    }
}