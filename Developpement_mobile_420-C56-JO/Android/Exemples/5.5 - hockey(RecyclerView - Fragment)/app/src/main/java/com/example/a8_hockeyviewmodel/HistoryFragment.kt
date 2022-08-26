package com.example.a8_hockeyviewmodel

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class HistoryFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        val root = inflater.inflate(R.layout.activity_history, container, false)
        val recyclerView: RecyclerView = root.findViewById(R.id.recyclerview)
        val viewModel = ViewModelProvider(this).get(ScoreViewModel::class.java)

        viewModel.getAllScore().observe(viewLifecycleOwner, Observer {
            val adapter = ScoreAdapter(activity!!)
            adapter.setScore(it)
            recyclerView.adapter = adapter
        })

        recyclerView.layoutManager = LinearLayoutManager(activity!!)

        return root
    }
}


