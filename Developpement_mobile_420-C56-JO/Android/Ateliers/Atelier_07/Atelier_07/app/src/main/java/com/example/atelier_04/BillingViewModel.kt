package com.example.atelier_04

import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import java.lang.NullPointerException

class BillingViewModel(): ViewModel() {

    private val _cost = MutableLiveData<Double>()
    private val _taxes = MutableLiveData<Boolean>()
    private val _tip = MutableLiveData<Int>()
    private val _total = MutableLiveData<Double>()
    private val _person = MutableLiveData<Int>()
    private val _byPerson = MutableLiveData<Double>()

    private val billingMutableData = MutableLiveData<Billing>()

    init {
        _cost.value = 0.0
        _taxes.value = false
        _tip.value = 5
        _total.value = 0.0
        _person.value = 1
        _byPerson.value = 0.0
    }

    val cost: LiveData<Double> = _cost
    val taxes: LiveData<Boolean> = _taxes
    val tip: LiveData<Int> = _tip
    val total: LiveData<Double> = _total
    val person: LiveData<Int> = _person
    val byPerson: LiveData<Double> = _byPerson

    fun getBilling(): LiveData<Billing> {
        return billingMutableData
    }

    fun onButtonClicked() {
        try {
            val billing = Billing(_cost.value!!, _taxes.value!!, _tip.value!!, _person.value!!)
            billingMutableData.value = billing
        }catch (e: NullPointerException) {
            Log.w("4.5 DataBinding", e.stackTrace.toString())
        }
    }

}
