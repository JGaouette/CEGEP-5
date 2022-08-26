package com.example.a6_fragment


import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ListView
import androidx.fragment.app.Fragment

/**
 * A simple [Fragment] subclass.
 */
class ListFragment : Fragment() {

    interface EntrainementListener{
        fun itemClicked(view: View, position: Int)
    }

    private var listener : EntrainementListener? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
        ): View? {
        return inflater.inflate(R.layout.listfragment, container, false)
    }

    override fun onAttach(context: Context) {
        super.onAttach(context);
        listener = context as EntrainementListener
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        var list = arrayOfNulls<String?>(0)

        val lv : ListView = view.findViewById(R.id.listView)
        for (entrainement in Entrainements) {
            list += entrainement.name
        }

        val adapter : ArrayAdapter<String?> = ArrayAdapter(requireContext(), android.R.layout.simple_list_item_1, list)
        lv.adapter = adapter

        lv.setOnItemClickListener { _, view, position, _ ->
            listener!!.itemClicked(view, position)
        }
    }
}




