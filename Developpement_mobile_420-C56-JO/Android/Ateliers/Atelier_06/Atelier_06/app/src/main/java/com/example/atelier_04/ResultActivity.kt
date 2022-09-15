package com.example.atelier_04

import android.content.Intent
import android.os.Bundle
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.atelier_04.databinding.ActivityMainBinding

class ResultActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_result)

        val intent = this.intent
        val brut = intent.getStringExtra("brut")
        val taxes = intent.getStringExtra("taxes")
        val total = intent.getStringExtra("total")
        val person = intent.getStringExtra("person")
        val byPerson = intent.getStringExtra("byPerson")


        val textBox : EditText = findViewById(R.id.edtCost)
        textBox.setText(byPerson)
    }
}