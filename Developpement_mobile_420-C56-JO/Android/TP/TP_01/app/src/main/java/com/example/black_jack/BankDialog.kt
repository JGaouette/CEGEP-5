package com.example.black_jack

import android.annotation.SuppressLint
import android.content.DialogInterface
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.WindowManager
import android.widget.TextView
import androidx.fragment.app.DialogFragment
import androidx.fragment.app.activityViewModels

class BankDialog : DialogFragment() {
    private val viewModel: MainViewModel by activityViewModels()
    private val bet = 0

    companion object {
        private const val KEY_TITLE = "KEY_TITLE"
        private const val KEY_BANK = "KEY_BANK"

        fun newInstance(title: String, bank: Int): BankDialog {
            val args = Bundle()
            args.putString(KEY_TITLE, title)
            args.putInt(KEY_BANK, bank)
            val fragment = BankDialog()
            fragment.arguments = args
            return fragment
        }
    }

    @SuppressLint("SetTextI18n")
    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val view = inflater.inflate(R.layout.fragment_bank_dialog, container, false)

        viewModel.bank.observe(this){ bank ->
            val txtBank = view.findViewById<TextView>(R.id.txtBank)
            txtBank.text = "$$bank"
        }

        return view
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {

        super.onViewCreated(view, savedInstanceState)
        setupView(view)
        setupClickListeners(view)
    }

    override fun onStart() {
        super.onStart()
        dialog?.window?.setLayout(
            WindowManager.LayoutParams.MATCH_PARENT,
            WindowManager.LayoutParams.WRAP_CONTENT
        )
    }


    override fun onDismiss(dialog: DialogInterface) {
        super.onDismiss(dialog)/*
         if(viewModel.inGame.value == false) {
             newInstance("Do not quit without reason!", viewModel.bank.value!!).show(parentFragmentManager, "bankDialog")
         }*/
        viewModel.inGame.value = true
    }

    @SuppressLint("SetTextI18n")
    private fun setupView(view: View) {
        val txtTitle = view.findViewById<TextView>(R.id.txtTitle)
        txtTitle.text = arguments?.getString(KEY_TITLE)

        val txtBank = view.findViewById<TextView>(R.id.txtBank)
        txtBank.text = "$" + arguments?.getInt(KEY_BANK).toString()
    }

    private fun setupClickListeners(view: View) {
        val btnBet = view.findViewById<TextView>(R.id.btnBet)
        val btnDebt = view.findViewById<TextView>(R.id.btnDebt)

        btnBet.setOnClickListener {
            val bet = view.findViewById<TextView>(R.id.txbBet).text.toString().toInt()

            if (bet < 0 || bet > viewModel.bank.value!!) {
                view.findViewById<TextView>(R.id.txtError).visibility = View.VISIBLE
                return@setOnClickListener
            }

            viewModel.sendBet(bet)
            dismiss()
        }

        btnDebt.setOnClickListener {
            viewModel.indebtedForLife()
        }
    }

}