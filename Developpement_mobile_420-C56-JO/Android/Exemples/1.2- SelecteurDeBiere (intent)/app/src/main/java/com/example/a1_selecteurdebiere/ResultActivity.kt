package com.example.a1_selecteurdebiere


import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class ResultActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_result)

        val intent = this.intent;
        val message = intent.getStringExtra("message")

        val label2 : TextView = findViewById(R.id.textView2)
        label2.text = String.format(getString(R.string.choice), message)
    }
}
