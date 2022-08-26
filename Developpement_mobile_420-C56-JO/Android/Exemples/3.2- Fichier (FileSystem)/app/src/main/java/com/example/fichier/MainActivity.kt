package com.example.fichier

import android.content.Context
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.util.Log
import android.widget.TextView
import java.io.BufferedReader
import java.io.FileNotFoundException
import java.io.InputStreamReader
import java.io.OutputStreamWriter


class MainActivity : AppCompatActivity() {

    var counter = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        try {
            openFileInput("counter.txt").use {
                val text = it.bufferedReader().use {
                    it.readText()
                }
                counter = if (text == "") 0 else text.toInt()
            }

            val tv : TextView = findViewById(R.id.tv)
            tv.text = counter.toString()
        }
        catch (e: FileNotFoundException){
            Log.w("test","test")
        }
    }

    override fun onStart() {
        super.onStart()
        try {
            openFileInput("counter.txt").use {
                val text = it.bufferedReader().use {
                    it.readText()
                }
                counter = if (text == "") 0 else text.toInt()
            }

            val tv : TextView = findViewById(R.id.tv)
            tv.text = counter.toString()
        }
        catch (e: FileNotFoundException){
            Log.w("test","test")
        }

    }

    override fun onStop() {
        super.onStop()
        try {
            val fileOut = openFileOutput("counter.txt", Context.MODE_PRIVATE)
            val outputWriter = OutputStreamWriter(fileOut)
            outputWriter.write(Integer.toString(++counter))
            outputWriter.close()
        } catch (e: Exception) {
            e.printStackTrace()
        }

    }
}
