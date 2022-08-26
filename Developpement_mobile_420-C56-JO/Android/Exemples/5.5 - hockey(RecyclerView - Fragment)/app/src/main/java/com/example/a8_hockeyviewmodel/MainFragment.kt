package com.example.a8_hockeyviewmodel

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.observe

class MainFragment : Fragment() {

    private lateinit var viewModel: ScoreViewModel

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment

        viewModel = ViewModelProvider(this).get(ScoreViewModel::class.java)

        val root = inflater.inflate(R.layout.fragment_main, container, false)
        val textA: TextView = root.findViewById(R.id.textA)
        val textB: TextView = root.findViewById(R.id.textB)

        viewModel.scoreA.observe(viewLifecycleOwner) { scoreA ->
            if (scoreA != null)
                textA.text = scoreA.toString()
            else
                textA.text = "0"
        }
        viewModel.scoreB.observe(viewLifecycleOwner, Observer { scoreB ->
            if (scoreB != null)
                textB.text = scoreB.toString()
            else
                textB.text = "0"
        })

        val btnScoreA : Button = root.findViewById(R.id.btnScoreA)
        val btnScoreB : Button = root.findViewById(R.id.btnScoreB)
        val btnCancel : Button = root.findViewById(R.id.btnCancel)


        btnScoreA.setOnClickListener  { _ -> viewModel.incrementScoreA() }
        btnScoreB.setOnClickListener  {_ -> viewModel.incrementScoreB() }
        btnCancel.setOnClickListener  { _-> viewModel.deleteLast() }

        return root
    }


}
