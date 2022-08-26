package com.example.a8_hockeyviewmodel

import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider


class MainActivity : AppCompatActivity() {

    private lateinit var viewModel: ScoreViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        viewModel = ViewModelProvider(this).get(ScoreViewModel::class.java)
        displayScore()
    }

    fun scoreA(v: View?) {
        viewModel.scoreA += 1
        displayScore()
    }

    fun cancelA(v: View?) {
        if (viewModel.scoreA > 0) viewModel.scoreA -= 1
        displayScore()
    }

    fun scoreB(v: View?) {
        viewModel.scoreB += 1
        displayScore()
    }

    fun cancelB(v: View?) {
        if (viewModel.scoreB > 0) viewModel.scoreB -= 1
        displayScore()
    }

    fun displayScore() {
        val tv_scoreA: TextView = findViewById(R.id.scoreA)
        val tv_scoreB: TextView = findViewById(R.id.scoreB)
        tv_scoreA.text = viewModel.scoreA.toString()
        tv_scoreB.text = viewModel.scoreB.toString()
    }

}
