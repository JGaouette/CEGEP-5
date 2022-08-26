package com.example.stopwatch

import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {

    private var seconds = 0
    private var running = false
    private var handlerAssigned = false
    private val handler: Handler = Handler()
    

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        /*
        if (savedInstanceState != null) {
            seconds = savedInstanceState.getInt("seconds");
            running = savedInstanceState.getBoolean("running");
        }
         */
    }

    /*
    override fun onSaveInstanceState(savedInstanceState: Bundle) {
        super.onSaveInstanceState(savedInstanceState)
        savedInstanceState.putInt("seconds", seconds)
        savedInstanceState.putBoolean("running", running)

        Log.i("StopWatch", "onSaveInstanceStates called")
    }
    */

    fun Start(view: View?) {
        running = true
        runTimer()
    }

    fun Stop(view: View?) {
        running = false
        showTimer()
        stopTimer()
    }

    fun Reset(view: View?) {
        running = false
        seconds = 0
        showTimer()
        stopTimer()
    }

    fun runTimer() {
        if (!handlerAssigned) {
            handler.post(object : Runnable {
                override fun run() {
                    showTimer();
                    if (running) seconds++
                    handler.postDelayed(this, 1000)
                    handlerAssigned = true
                }
            })
        }
    }

    fun stopTimer() {
        handler.removeCallbacksAndMessages(null)
        handlerAssigned = false
    }

    fun showTimer() {
        val tv: TextView = findViewById(R.id.chrono)
        val hours = seconds / 3600
        val minutes = seconds % 3600 / 60
        val secs = seconds % 60
        val time = String.format("%02d:%02d:%02d", hours, minutes, secs)
        tv.text = time
    }



}
