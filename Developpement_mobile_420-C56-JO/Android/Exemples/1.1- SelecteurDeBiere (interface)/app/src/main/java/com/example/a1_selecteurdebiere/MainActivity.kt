package com.example.a1_selecteurdebiere

import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.Spinner
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import java.util.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val selectedBeerButton : Button = findViewById(R.id.selectBeer_button)
        val chosenBeer: Spinner = findViewById(R.id.beerArray_spinner)

        selectedBeerButton.setOnClickListener{
            var text = String.format(getString(R.string.choice),
                chosenBeer.selectedItem.toString().decapitalize(Locale.ROOT))
            Toast.makeText(this, text,
                Toast.LENGTH_LONG).show()
            Log.w(String.format(getString(R.string.app_name)),
                "Button clicked with " + chosenBeer.selectedItem.toString())
        }
    }
}
