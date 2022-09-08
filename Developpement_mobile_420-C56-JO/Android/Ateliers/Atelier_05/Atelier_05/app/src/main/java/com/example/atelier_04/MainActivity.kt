package com.example.atelier_04

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.atelier_04.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding : ActivityMainBinding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        var hasTaxes = false

        binding.tgbTaxes.setOnClickListener{
            hasTaxes = binding.tgbTaxes.isChecked
        }

        binding.btnCalculate.setOnClickListener{
            var cost = 0.00
            if(binding.ednCost.text.toString() != "")
                cost = binding.ednCost.text.toString().toDouble()

            var tip = binding.spnTip.selectedItem.toString().toDouble() / 100.0
            var person = binding.spnPerson.selectedItem.toString().toDouble()
            var taxes = 0.00

            if(hasTaxes) taxes = cost * 0.14975

            var amount = ((cost + taxes) + ((cost + taxes) * tip)) / person
            val formatted = String.format("%.2f", amount)

            val intent = Intent(this, ResultActivity::class.java).apply {
                putExtra("data", "$formatted$")
            }
            //Toast.makeText(this, "$formatted$",Toast.LENGTH_LONG).show()

            startActivity(intent)
        }
    }
}