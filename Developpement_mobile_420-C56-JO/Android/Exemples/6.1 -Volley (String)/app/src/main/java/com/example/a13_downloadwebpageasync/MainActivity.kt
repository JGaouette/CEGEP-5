package com.example.a13_downloadwebpageasync

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.TextView
import com.android.volley.Request
import com.android.volley.Response
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley


class MainActivity : AppCompatActivity(){

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun download(v : View) {

        val queue = Volley.newRequestQueue(this)
        val urlEdit : EditText = findViewById(R.id.tvURL)
        val url = urlEdit.text.toString()
        val responseText: TextView = findViewById(R.id.tvResponse)

        val stringRequest = StringRequest(
            // Requête get
            Request.Method.GET,
            // l'URL
            url,
            { response ->
                responseText.text = response
            },
            {
                responseText.text =  "Erreur de téléchargement " + it.toString()
            }
        )

        // On émet la requête
        queue.add(stringRequest)


    }
}