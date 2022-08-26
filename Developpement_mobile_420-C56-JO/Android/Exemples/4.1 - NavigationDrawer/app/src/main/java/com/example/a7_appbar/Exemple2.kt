package com.example.a7_appbar


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.Toolbar
import androidx.navigation.fragment.findNavController

/**
 * A simple [Fragment] subclass.
 */
class Exemple2 : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        val root = inflater.inflate(R.layout.fragment_exemple2, container, false)
        val button : Button = root.findViewById(R.id.button_fragment2)
        button.setOnClickListener {
                findNavController().navigate(R.id.action_exemple2_to_exemple_final)
        }

        return root
    }


}
