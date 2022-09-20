package com.example.atelier_04

data class Billing(var Cost:Double, var IsTaxed:Boolean, var Tip:Int, var Person:Int) {
    fun calculateTip():Double{
        return Cost * Tip / 100
    }

    fun calculateTaxes():Double{
        return if (IsTaxed) Cost * 0.14975 else 0.0
    }

    fun calculateTotal():Double{
        return Cost + calculateTip() + calculateTaxes()
    }

    fun calculatePerPerson():Double{
        return calculateTotal() / Person
    }
}