package com.example.appbarsimple

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.appcompat.widget.Toolbar
import com.google.android.material.appbar.CollapsingToolbarLayout

class MainActivity2 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main2)
        val toolbar: Toolbar? = findViewById(R.id.toolbar)
        val toolbarLayout: CollapsingToolbarLayout? = findViewById(R.id.toolbar_layout)
        toolbarLayout?.title = title
        setSupportActionBar(toolbar)
    }
}