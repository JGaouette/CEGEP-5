package com.example.simon

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.CountDownTimer
import android.util.Log
import android.view.View
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.lifecycle.ViewModelProvider
import java.io.File
import java.io.FileNotFoundException
import java.io.FileOutputStream
import java.io.OutputStreamWriter

class MainActivity : AppCompatActivity() {
    private lateinit var viewModel: ViewModel
    lateinit var btnGreen: Button
    lateinit var btnRed: Button
    lateinit var btnYellow: Button
    lateinit var btnBlue: Button


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btnGreen = findViewById(R.id.btnGreen)
        btnRed = findViewById(R.id.btnRed)
        btnYellow = findViewById(R.id.btnYellow)
        btnBlue = findViewById(R.id.btnBlue)

        viewModel = ViewModelProvider(this)[ViewModel::class.java]

        setupView()
        setupClickListeners()
        setupObservers()

        viewModel.addGoodSequence()
    }

    private fun setupView(){
        val file : File

        try {
            file = File(this.filesDir, "simon.csv")
            val lines = file.readLines()
            findViewById<TextView>(R.id.txtScore).text = lines[0]
        }
        catch (e: FileNotFoundException){ }
    }

    @SuppressLint("SetTextI18n")
    private fun setupObservers(){
        viewModel.getGoodSequence().observe(this){ sequence ->
            for (nb in sequence){
                object:  CountDownTimer(1000,500){
                    override fun onTick(millisUntilFinished: Long) {
                        // s'exécute après 500 ms
                    }
                    override fun onFinish() {
                        when (nb) {
                            0 -> {
                                changeGreenOnClick()
                            }
                            1 -> {
                                changeRedOnClick()
                            }
                            2 -> {
                                changeYellowOnClick()
                            }
                            3 -> {
                                changeBlueOnClick()
                            }
                        }
                    }
                }.start()
            }
        }

        viewModel.getUserSequence().observe(this){ sequence ->
            if (sequence.isNotEmpty()){
                for (i in sequence.indices){
                    if (sequence[i] != viewModel.goodSequence.value?.get(i)){
                        Toast.makeText(this, "Vous avez perdu avec un score de " + viewModel.getScore().value, Toast.LENGTH_SHORT).show()
                        viewModel.reset()
                        return@observe
                    }

                    if (i == viewModel.getGoodSize()?.minus(1)){
                        viewModel.addGoodSequence()
                        viewModel.addScore()
                    }
                }
            }
        }

        viewModel.getScore().observe(this){score ->
            findViewById<TextView>(R.id.txtScore).text = "Score: $score"

            if (score > viewModel.getHighScore().value!!){
                viewModel.setHighScore()
            }
        }

        viewModel.getHighScore().observe(this){highScore ->
            try {
                val file = File(this.filesDir, "simon.csv")

                var fileOutput = FileOutputStream(file, true)
                val outputWriter = OutputStreamWriter(fileOutput)

                if (!file.exists())
                    file.createNewFile()

                outputWriter.write("Plus haut score: $highScore")
                outputWriter.flush()
                outputWriter.close()
            } catch (e: Exception) {
                e.printStackTrace()
            }

            findViewById<TextView>(R.id.txtHighScore).text = "Plus haut score: $highScore"
        }

    }

    private fun setupClickListeners() {
        btnGreen.setOnClickListener {
            changeGreenOnClick()
            viewModel.addUserSequence(0)
        }

        btnRed.setOnClickListener {
            changeRedOnClick()
            viewModel.addUserSequence(1)
        }

        btnYellow.setOnClickListener {
            changeYellowOnClick()
            viewModel.addUserSequence(2)
        }

        btnBlue.setOnClickListener {
            changeBlueOnClick()
            viewModel.addUserSequence(3)
        }
    }

    private fun changeGreenOnClick(){
        object:CountDownTimer(1000,500){
            override fun onTick(millisUntilFinished: Long) {
                btnGreen.isEnabled = false
            }
            override fun onFinish() {
                btnGreen.isEnabled = true
            }
        }.start()
    }

    private fun changeRedOnClick(){
        object:CountDownTimer(1000,500){
            override fun onTick(millisUntilFinished: Long) {
                btnRed.isEnabled = false
            }
            override fun onFinish() {
                btnRed.isEnabled = true
            }
        }.start()
    }

    private fun changeYellowOnClick(){
        object:CountDownTimer(1000,500){
            override fun onTick(millisUntilFinished: Long) {
                btnYellow.isEnabled = false
            }
            override fun onFinish() {
                btnYellow.isEnabled = true
            }
        }.start()
    }

    private fun changeBlueOnClick(){
        object:CountDownTimer(1000,500){
            override fun onTick(millisUntilFinished: Long) {
                btnBlue.isEnabled = false
            }
            override fun onFinish() {
                btnBlue.isEnabled = true
            }
        }.start()
    }
}
