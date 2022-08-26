package com.example.a6_fragment


import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView

/**
 * A simple [Fragment] subclass.
 */
class DetailFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {

        val root = inflater.inflate(R.layout.detailfragment, container, false)

        val name : TextView = root.findViewById(R.id.name)
        val description : TextView = root.findViewById(R.id.description)
        val link : TextView = root.findViewById(R.id.link)

        val pos = arguments?.getInt("position") ?: 0
        name.text = Entrainements[pos].name
        description.text = Entrainements[pos].description
        link.text = Entrainements[pos].link

        return root
    }
}



