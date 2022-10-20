package com.example.black_jack

import android.annotation.SuppressLint
import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.FrameLayout
import androidx.core.view.isInvisible
import androidx.lifecycle.ViewModelProvider
import kotlin.math.log

class StatsFragment : Fragment() {
    private lateinit var viewModel: MainViewModel

    @SuppressLint("CutPasteId")
    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val view = inflater.inflate(R.layout.fragment_stats, container, false)
        val fragContainer = view.findViewById<FrameLayout>(R.id.fragment_container)

        viewModel = ViewModelProvider(this)[MainViewModel::class.java]

        viewModel.statsIsVisible().observe(viewLifecycleOwner) { isVisible ->
            if (isVisible) {
                fragContainer.visibility = View.VISIBLE
            } else {
                fragContainer.visibility = View.INVISIBLE
            }
        }

        /*
        view.findViewById<FrameLayout>(R.id.btnHideStats).setOnClickListener {
            fragContainer.visibility = View.INVISIBLE
        }
*/
        return inflater.inflate(R.layout.fragment_stats, container, false)
    }
}