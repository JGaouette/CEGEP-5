package com.example.a8_hockeyviewmodel

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView


class History : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_history)

        val recyclerView: RecyclerView = findViewById(R.id.recyclerview)


        val viewModel = ViewModelProvider(this).get(ScoreViewModel::class.java)
        viewModel.getAllScore().observe(this, {
            val adapter = ScoreAdapter(this)
            adapter.setScore(it)
            recyclerView.adapter = adapter
        })

        recyclerView.layoutManager = LinearLayoutManager(this)
    }
}
