package com.example.a81testsunitaires

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.TextView
import java.lang.NumberFormatException

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun calculate(v: View) {
        val tv = findViewById<TextView>(R.id.output)
        val text1 = findViewById<EditText>(R.id.text1).text.toString()
        val text2 = findViewById<EditText>(R.id.text2).text.toString()

        try {
            var math = Math(text1, text2)
            tv.text = math.PGCD().toString()
        }
        catch (e: NumberFormatException) {
            tv.text = "Format d'entrée incorrect"
        }

    }
}