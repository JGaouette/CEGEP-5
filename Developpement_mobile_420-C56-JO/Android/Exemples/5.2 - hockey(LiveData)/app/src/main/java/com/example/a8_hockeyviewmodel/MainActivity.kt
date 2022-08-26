package com.example.a8_hockeyviewmodel

import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.TextView
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

    fun goalA(v: View?) {
        viewModel.incrementScoreA()
    }

    fun cancelA(v: View?) {
        viewModel.decrementScoreA()
    }

    fun goalB(v: View?) {
        viewModel.incrementScoreB()
    }

    fun cancelB(v: View?) {
        viewModel.decrementScoreB()
    }

}
