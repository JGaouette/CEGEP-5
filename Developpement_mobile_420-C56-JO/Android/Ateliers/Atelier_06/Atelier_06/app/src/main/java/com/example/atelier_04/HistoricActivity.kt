package com.example.atelier_04

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.atelier_04.databinding.ActivityHistoricBinding
import java.io.File
import java.io.FileInputStream
import java.io.FileNotFoundException

class HistoricActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding : ActivityHistoricBinding = ActivityHistoricBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val file : File

        try {
            file = File(this.filesDir, "counter.txt")
            val fileInput = FileInputStream(file.path)
            val fileReader = fileInput.bufferedReader()
            var text = fileReader.readLine()

        }
        catch (e: FileNotFoundException){
            Log.w("test","test")
        }

    }
}