package com.example.a8_hockeyviewmodel

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider


class MainActivity : AppCompatActivity() {

    private lateinit var viewModel: ScoreViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val tvscoreA: TextView = findViewById(R.id.scoreA)
        val tvscoreB: TextView = findViewById(R.id.scoreB)

        viewModel = ViewModelProvider(this).get(ScoreViewModel::class.java)


        viewModel.scoreA.observe(this, Observer { scoreA ->
            tvscoreA.text = scoreA.toString()
        })
        viewModel.scoreB.observe(this, Observer { scoreB ->
            tvscoreB.text = scoreB.toString()
        })
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.main_menu, menu)
        return true
    }

    fun goalA(v: View?) {
        viewModel.incrementScoreA()
    }

    fun goalB(v: View?) {
        viewModel.incrementScoreB()
    }

    fun cancel(v: View?) {
        viewModel.deleteLast()
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.history -> {
                val i = Intent (this, com.example.a8_hockeyviewmodel.History::class.java)
                startActivity(i)
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }
}
