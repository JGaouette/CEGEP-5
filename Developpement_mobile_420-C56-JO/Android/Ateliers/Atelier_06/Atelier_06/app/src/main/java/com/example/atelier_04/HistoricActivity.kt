package com.example.atelier_04

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.atelier_04.databinding.ActivityHistoricBinding
import java.io.File
import java.io.FileInputStream
import java.io.FileNotFoundException


class HistoricActivity : AppCompatActivity() {
    var historic = ""

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding : ActivityHistoricBinding = ActivityHistoricBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val file : File

        try {
            file = File(this.filesDir, "historic.txt")
            val fileInput = FileInputStream(file.path)
            val fileReader = fileInput.bufferedReader()
            fileReader.useLines {
                it.map { line ->
                    var text = binding.textView7.text
                    binding.textView7.text = "$text \n $line"
                }
            }
            //var text = fileReader.readLine()

        }
        catch (e: FileNotFoundException){
            Log.w("test","test")
        }
    }
}