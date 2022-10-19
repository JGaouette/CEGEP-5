package com.example.black_jack

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase

@Database(entities = [Stats::class], version = 1)
abstract class StatsDatabase : RoomDatabase() {
    abstract fun statsDAO(): StatsDAO

    companion object Database {
        fun getDatabase(context: Context): StatsDatabase {
            return Room.databaseBuilder(
                context,
                StatsDatabase::class.java, "StatsDatabase"
            )
                .addMigrations(this.MIGRATION_1_2)
                .addMigrations(this.MIGRATION_2_3)
                .allowMainThreadQueries()
                .build()
        }

        private val MIGRATION_1_2 = object : Migration(1, 2) {
            override fun migrate(database: SupportSQLiteDatabase) {
                database.execSQL("DELETE FROM Stats")
            }
        }

        private val MIGRATION_2_3 = object : Migration(2, 3) {
            override fun migrate(database: SupportSQLiteDatabase) {
                database.execSQL("DELETE FROM Stats")
            }
        }

    }
}