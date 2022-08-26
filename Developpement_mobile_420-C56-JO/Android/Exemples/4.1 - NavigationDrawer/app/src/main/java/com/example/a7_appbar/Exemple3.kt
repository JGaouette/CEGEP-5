package com.example.a7_appbar


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.navigation.fragment.findNavController

/**
 * A simple [Fragment] subclass.
 */
class Exemple3 : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val root = inflater.inflate(R.layout.fragment_exemple3, container, false)
        val button : Button = root.findViewById(R.id.button_fragment3)

        button.setOnClickListener {
            findNavController().navigate(R.id.action_exemple3_to_exemple_final)
        }


        return root
    }


}
