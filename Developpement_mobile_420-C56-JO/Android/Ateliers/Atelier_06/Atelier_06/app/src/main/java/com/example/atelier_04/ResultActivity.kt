package com.example.atelier_04

import android.content.Intent
import android.os.Bundle
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.atelier_04.databinding.ActivityResultBinding
import java.io.File
import java.io.FileOutputStream
import java.io.OutputStreamWriter

class ResultActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding : ActivityResultBinding = ActivityResultBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val intent = this.intent
        val subtotal = intent.getStringExtra("subtotal")
        val taxes = intent.getStringExtra("taxes")
        val total = intent.getStringExtra("total")
        val person = intent.getStringExtra("person")
        val byPerson = intent.getStringExtra("byPerson")

        binding.ednSubtotal.setText(subtotal)
        binding.ednTaxes.setText(taxes)
        binding.ednTotal.setText(total)
        var newText = binding.edtByPerson.text.replace("x".toRegex(), person!!)
        binding.edtByPerson.setText(newText)
        binding.ednByPerson.setText(byPerson)

        binding.btnSave.setOnClickListener{
            try {
                val file = File(this.filesDir, "historic.csv")
                var fileOutput = FileOutputStream(file)
                val outputWriter = OutputStreamWriter(fileOutput)

                outputWriter.append("Subtotal: $subtotal, Taxes: $taxes, Total: $total, By person ($person): $byPerson")
                outputWriter.close()
            } catch (e: Exception) {
                e.printStackTrace()
            }

            binding.btnSave.isEnabled = false

            Toast.makeText(this, "The billing has been saved",Toast.LENGTH_LONG).show()
        }

        binding.btnHistoric.setOnClickListener{
            val intent = Intent(this, HistoricActivity::class.java).apply {}
            startActivity(intent)
        }
    }
}