package com.example.appbarsimple

import android.content.Intent
import android.os.Bundle
import android.view.Menu
import android.view.MenuInflater
import android.view.MenuItem
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.widget.Toolbar
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val toolbar: Toolbar? = findViewById(R.id.toolbar)
        setSupportActionBar(toolbar)
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        super.onCreateOptionsMenu(menu)
        menuInflater.inflate(R.menu.menu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        super.onOptionsItemSelected(item)
        val tv = findViewById<TextView>(R.id.tv)
        when (item.itemId) {
            R.id.mi_compose -> {
                tv.text = "Composition"
                return true
            }
            R.id.mi_settings -> {
                tv.text = "Paramètres"
                return true
            }
            R.id.patate -> {
                tv.text = "PATATATATATATATATE"
                return true
            }
            R.id.sa -> {
                tv.text = "scroll"
                val i = Intent (this, MainActivity2::class.java)
                startActivity(i)
                return true
            }
        }

        return false
    }
}