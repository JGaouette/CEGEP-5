package com.example.atelier_04

import android.os.Bundle
import android.util.Log
import android.widget.ArrayAdapter
import androidx.appcompat.app.AppCompatActivity
import com.example.atelier_04.databinding.ActivityHistoricBinding
import java.io.File
import java.io.FileNotFoundException


class HistoricActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding : ActivityHistoricBinding = ActivityHistoricBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val file : File

        try {
            file = File(this.filesDir, "historic.csv")
            val lines = file.readLines()
            val list = lines.toMutableList()

            val adapter: ArrayAdapter<String> = ArrayAdapter(
                this,
                android.R.layout.simple_dropdown_item_1line,list
            )

            // attach the array adapter with list view
            binding.listviewBillings.adapter = adapter
            adapter.notifyDataSetChanged()

        }
        catch (e: FileNotFoundException){
            Log.w("test","test")
        }
    }
}