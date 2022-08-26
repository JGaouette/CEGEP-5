package com.example.a8_hockeyviewmodel

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase

@Database(entities = arrayOf(Score::class), version = 6, exportSchema = false)
abstract class ScoreDatabase : RoomDatabase(){
    abstract fun scoreDAO() : ScoreDAO


    companion object {
        // Singleton prevents multiple instances of database opening at the
        // same time.
        @Volatile
        private var INSTANCE: ScoreDatabase? = null

        fun getDatabase(context: Context): ScoreDatabase {
            return  INSTANCE ?: synchronized(this) {
                INSTANCE ?: Room.databaseBuilder(
                    context.applicationContext,
                    ScoreDatabase::class.java, "scoreDatabase"
                )
                    .fallbackToDestructiveMigration()
                    .build()
            }
        }
    }
}