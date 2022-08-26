package com.example.a1_selecteurdebiere

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.a1_selecteurdebiere.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding : ActivityMainBinding = ActivityMainBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)

        binding.button.setOnClickListener {
            val beer = binding.beerChooserSpinner.selectedItem.toString().decapitalize()
            val intent = Intent(this, ResultActivity::class.java).apply {
                putExtra("message", beer)
            }

            startActivity(intent)
        }
    }


}
