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
import android.widget.TableLayout
import android.widget.TextView
import androidx.core.view.isInvisible
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.ViewModelProvider
import kotlin.math.log
import kotlin.math.round
import kotlin.math.roundToInt

class StatsFragment : Fragment() {
    private val viewModel: MainViewModel by activityViewModels()

    @SuppressLint("CutPasteId", "SetTextI18n")
    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val view = inflater.inflate(R.layout.fragment_stats, container, false)
        val fragContainer = view.findViewById<FrameLayout>(R.id.fragment_container)
        val btnHideStats = view.findViewById<Button>(R.id.btnHideStats)

        viewModel.statsIsVisible().observe(viewLifecycleOwner) { isVisible ->
            if (isVisible) {
                fragContainer.visibility = View.VISIBLE
                updateStats(view)
            } else {
                fragContainer.visibility = View.INVISIBLE
            }
        }

        btnHideStats.setOnClickListener {
            viewModel.setStatsVisible(false)
        }

        viewModel.getRemainingCards().observe(viewLifecycleOwner) { remainingCards ->
            val txtCardLeftNumber = view.findViewById<TextView>(R.id.txtCardLeftNumber)
            txtCardLeftNumber.text = remainingCards.toString()

            val txtAsLeft = view.findViewById<TextView>(R.id.txtAsLeft)
            txtAsLeft.text = viewModel.getStatNumber("As").toString()
            val txtAsPercent = view.findViewById<TextView>(R.id.txtAsPercent)
            txtAsPercent.text = (viewModel.getStatNumber("As").toDouble() / remainingCards.toDouble() * 100).toString().take(4) + "%"

            val txt10Left = view.findViewById<TextView>(R.id.txt10Left)
            txt10Left.text = viewModel.getStatNumber("10").toString()
            val txt10Percent = view.findViewById<TextView>(R.id.txt10Percent)
            txt10Percent.text = (viewModel.getStatNumber("10").toDouble() / remainingCards.toDouble() * 100).toString().take(4) + "%"

            val txt9Left = view.findViewById<TextView>(R.id.txt9Left)
            txt9Left.text = viewModel.getStatNumber("9").toString()
            val txt9Percent = view.findViewById<TextView>(R.id.txt9Percent)
            txt9Percent.text = (viewModel.getStatNumber("9").toDouble() / remainingCards.toDouble()* 100).toString().take(4) + "%"

            val txt8Left = view.findViewById<TextView>(R.id.txt8Left)
            txt8Left.text = viewModel.getStatNumber("8").toString()
            val txt8Percent = view.findViewById<TextView>(R.id.txt8Percent)
            txt8Percent.text = (viewModel.getStatNumber("8").toDouble() / remainingCards.toDouble()* 100).toString().take(4) + "%"

            val txt7Left = view.findViewById<TextView>(R.id.txt7Left)
            txt7Left.text = viewModel.getStatNumber("7").toString()
            val txt7Percent = view.findViewById<TextView>(R.id.txt7Percent)
            txt7Percent.text = (viewModel.getStatNumber("7").toDouble() / remainingCards.toDouble()* 100).toString().take(4) + "%"

            val txt6Left = view.findViewById<TextView>(R.id.txt6Left)
            txt6Left.text = viewModel.getStatNumber("6").toString()
            val txt6Percent = view.findViewById<TextView>(R.id.txt6Percent)
            txt6Percent.text = (viewModel.getStatNumber("6").toDouble() / remainingCards.toDouble()* 100).toString().take(4) + "%"

            val txt5Left = view.findViewById<TextView>(R.id.txt5Left)
            txt5Left.text = viewModel.getStatNumber("5").toString()
            val txt5Percent = view.findViewById<TextView>(R.id.txt5Percent)
            txt5Percent.text = (viewModel.getStatNumber("5").toDouble() / remainingCards.toDouble()* 100).toString().take(4) + "%"

            val txt4Left = view.findViewById<TextView>(R.id.txt4Left)
            txt4Left.text = viewModel.getStatNumber("4").toString()
            val txt4Percent = view.findViewById<TextView>(R.id.txt4Percent)
            txt4Percent.text = (viewModel.getStatNumber("4").toDouble() / remainingCards.toDouble()* 100).toString().take(4) + "%"

            val txt3Left = view.findViewById<TextView>(R.id.txt3Left)
            txt3Left.text = viewModel.getStatNumber("3").toString()
            val txt3Percent = view.findViewById<TextView>(R.id.txt3Percent)
            txt3Percent.text = (viewModel.getStatNumber("3").toDouble() / remainingCards.toDouble() * 100).toString().take(4) + "%"

            val txt2Left = view.findViewById<TextView>(R.id.txt2Left)
            txt2Left.text = viewModel.getStatNumber("2").toString()
            val txt2Percent = view.findViewById<TextView>(R.id.txt2Percent)
            txt2Percent.text = (viewModel.getStatNumber("2").toDouble() / remainingCards.toDouble() * 100).toString().take(4) + "%"
        }

        return view
    }

    @SuppressLint("SetTextI18n")
    fun updateStats(view: View) {

    }

}