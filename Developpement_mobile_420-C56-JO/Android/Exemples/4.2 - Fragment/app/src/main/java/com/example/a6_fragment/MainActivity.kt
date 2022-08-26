package com.example.a6_fragment

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import androidx.navigation.findNavController

class MainActivity : AppCompatActivity(), ListFragment.EntrainementListener{

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    override fun itemClicked(view : View, position: Int){
        var bundle = Bundle().apply{
            putInt("position", position)
        }

        val navhost = findNavController(R.id.nav_host_fragment)
        navhost.navigate(R.id.detailFragment, bundle)
    }
}
