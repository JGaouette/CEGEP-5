package com.example.a8_hockeyviewmodel

import android.content.Context
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.RecyclerView.ViewHolder
import java.text.SimpleDateFormat
import java.util.*


class ScoreAdapter(context : Context) : RecyclerView.Adapter<ScoreAdapter.ScoreViewHolder>() {

    private val _inflater : LayoutInflater = LayoutInflater.from(context)
    private lateinit var _score : List<Score>

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ScoreViewHolder {
        val itemView: View =
            _inflater.inflate(R.layout.recyclerview_item, parent, false)

        itemView.setOnClickListener{
            Log.d("hockey", it.tag.toString())
        }
        return ScoreViewHolder(itemView)
    }

    override fun getItemCount(): Int {
        return _score.size
    }

    override fun onBindViewHolder(holder: ScoreViewHolder, position: Int) {
        var current = _score[position]
        val formatter = SimpleDateFormat("hh:mm:ss")
        val calendar: Calendar = Calendar.getInstance()
        calendar.timeInMillis = current.date

        holder.scoreATV.text = current.scoreA.toString()
        holder.scoreBTV.text = current.scoreB.toString()
        holder.scoreMoment.text = formatter.format(calendar.time).toString()

        holder.itemView.tag = current.date
    }

    class ScoreViewHolder (itemView: View) : ViewHolder(itemView) {
        var scoreATV: TextView = itemView.findViewById( R.id.tvA)
        var scoreBTV: TextView = itemView.findViewById(R.id.tvB)
        var scoreMoment: TextView = itemView.findViewById(R.id.tvMoment)

    }

    fun setScore(score: List<Score>) {
        _score = score
    }


}