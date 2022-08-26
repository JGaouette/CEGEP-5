package com.example.a8_hockeyviewmodel

import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.room.Room


class MainActivity : AppCompatActivity() {

    private lateinit var viewModel: ScoreViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val tvscoreA: TextView = findViewById(R.id.scoreA)
        val tvscoreB: TextView = findViewById(R.id.scoreB)

        viewModel = ViewModelProvider(this).get(ScoreViewModel::class.java)
        viewModel.scoreA.observe(this, Observer { scoreA ->
            if (scoreA != null)
                tvscoreA.text = scoreA.toString()
            else
                tvscoreA.text = "0"
        })
        viewModel.scoreB.observe(this, Observer { scoreB ->
            if (scoreB != null)
                tvscoreB.text = scoreB.toString()
            else
                tvscoreB.text = "0"
        })
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

}
