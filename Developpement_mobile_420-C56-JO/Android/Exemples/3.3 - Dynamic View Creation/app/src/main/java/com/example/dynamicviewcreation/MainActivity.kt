package com.example.dynamicviewcreation

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.LinearLayout
import android.widget.TextView
import java.io.File
import java.io.FileOutputStream

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var fichier = File(filesDir, "patate.txt")
        FileOutputStream(fichier, true).writer().use {
            it.write("Bonjour les amis 1")
        }

        var contenu = fichier.reader().use {
            it.readText()
        }

        Log.w("Fichier", contenu)

        FileOutputStream(fichier, true).writer().use {
            it.write("Bonjour les amis 2")
        }


        // var content = fichier.readText()
        val layout = findViewById<LinearLayout>(R.id.layout)

        val tv = TextView(this)
        tv.text = contenu
        layout.addView(tv)
    }
}