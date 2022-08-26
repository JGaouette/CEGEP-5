package com.example.a13_downloadwebpageasync

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.TextView

class MainActivity : AppCompatActivity() , getURLTask.AsyncResponse {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    override fun processFinish(Output: String) {
        val tvResponse : TextView = findViewById(R.id.tvResponse)
        tvResponse.text = Output
    }

    fun download(v : View) {
        val urlEdit : EditText = findViewById(R.id.tvURL)
        val url = urlEdit.text.toString()

        val task = getURLTask()
        task.ui = this
        task.execute(url)
    }
}
