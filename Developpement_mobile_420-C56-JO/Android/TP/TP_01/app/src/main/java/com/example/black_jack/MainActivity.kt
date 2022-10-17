package com.example.black_jack

import android.graphics.Bitmap
import android.graphics.drawable.BitmapDrawable
import android.os.Bundle
import android.widget.Button
import android.widget.ImageView
import android.widget.LinearLayout
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.ConstraintLayout
import kotlin.math.round


class MainActivity : AppCompatActivity() {
    private lateinit var jeuCarte: ImageView
    private lateinit var dealerLayout: LinearLayout
    private lateinit var playerLayout: LinearLayout
    private var playerCards = 0
    private var dealerCards = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val mainLayout = findViewById<ConstraintLayout>(R.id.mainLayout)
        val btnHit = findViewById<Button>(R.id.btnHit)
        val btnStand = findViewById<Button>(R.id.btnStand)

        dealerLayout = findViewById(R.id.dealerLayout)
        playerLayout = findViewById(R.id.playerLayout)

        btnHit.setOnClickListener {
            val carte = ImageView(this)
            //carte.setImageBitmap(getCard("2","Coeur"))
            carte.setImageBitmap(getRandomCard())
            addCardToLayout(playerLayout, carte)
            playerCards++
        }

        jeuCarte = ImageView(this)
        jeuCarte.setImageResource(R.drawable.jeu_carte)
    }

    private fun addCardToLayout(layout: LinearLayout, card: ImageView) {
        val cardNumber: Int = if(layout.id == dealerLayout.id){
            dealerCards
        }else{
            playerCards
        }

        card.x = -((layout.width - cardNumber * 150) / 3).toFloat()
        card.y = 0f - (cardNumber * 27.0 * 2).toFloat()

        layout.addView(card)

        //Show card y with toast
        Toast.makeText(this, "Card Y: ${card.y}", Toast.LENGTH_SHORT).show()

    }

    private fun getRandomCard(): Bitmap {
        val col: Int = (1..13).random()
        val row: Int = (1..4).random()
        val offset: Int = when (col) {
            1 -> 0
            else -> 1
        }

        val width = 192
        val height = 27.0
        return Bitmap.createBitmap(
            (jeuCarte.drawable as BitmapDrawable).bitmap,
            (col - 1) * width + offset,
            round((row - 1) * height).toInt(),
            width,
            round(height).toInt()
        )
    }

    private fun getCard(rank: String, suit: String): Bitmap {
        val col: Int = when (rank) {
            "As" -> 1
            "2" -> 2
            "3" -> 3
            "4" -> 4
            "5" -> 5
            "6" -> 6
            "7" -> 7
            "8" -> 8
            "9" -> 9
            "10" -> 10
            "Valet" -> 11
            "Reine" -> 12
            "Roi" -> 13
            else -> 0
        }

        val row: Int = when (suit) {
            "Trèfle" -> 1
            "Carreau" -> 2
            "Coeur" -> 3
            "Pique" -> 4
            else -> 0
        }

        val offset: Int = when (rank) {
            "As" -> 0
            else -> 1
        }

        val width = 192
        val height = 279.5
        return Bitmap.createBitmap(
            (jeuCarte.drawable as BitmapDrawable).bitmap,
            (col - 1) * width + offset,
            round((row - 1) * height).toInt(),
            width,
            round(height).toInt()
        )
    }


    private fun getCover(): Bitmap {
        val width = 192
        val height = 279.5
        return Bitmap.createBitmap(
            (jeuCarte.drawable as BitmapDrawable).bitmap,
            384,
            1117,
            192,
            279
        )
    }
}

