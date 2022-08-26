package com.example.login

import android.os.Bundle
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.constraintlayout.widget.ConstraintSet
import androidx.transition.TransitionManager
import com.example.login.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        var set = false
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        val view = binding.root
        setContentView(view)

        val constraint1 = ConstraintSet()
        constraint1.clone(this, R.layout.activity_main)
        val constraint2 = ConstraintSet()
        constraint2.clone(this, R.layout.activity_main_end)

        binding.chat.setOnClickListener{
            TransitionManager.beginDelayedTransition(binding.layout)
            val constraint = if(set) constraint1 else constraint2
            constraint.applyTo(binding.layout)
            set = !set
        }
    }
}
