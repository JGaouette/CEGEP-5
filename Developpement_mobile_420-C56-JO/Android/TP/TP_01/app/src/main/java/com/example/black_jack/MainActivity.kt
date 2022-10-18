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
import androidx.lifecycle.ViewModelProvider
import kotlin.math.round


class MainActivity : AppCompatActivity() {
    private lateinit var jeuCarte: ImageView
    private lateinit var dealerLayout: LinearLayout
    private lateinit var playerLayout: LinearLayout
    private lateinit var scrollLayout: LinearLayout
    private var playerCards = 0
    private var dealerCards = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var viewModel = ViewModelProvider(this)[ViewModel::class.java]
        val btnHit = findViewById<Button>(R.id.btnHit)
        val btnStand = findViewById<Button>(R.id.btnStand)

        dealerLayout = findViewById(R.id.dealerLayout)
        playerLayout = findViewById(R.id.playerLayout)
        scrollLayout = findViewById(R.id.playerLayout)

        viewModel.getDeck().observe(this){ deck ->
            Toast.makeText(this, "Deck id: ${deck.deckId}", Toast.LENGTH_SHORT).show()



            btnHit.setOnClickListener {
                viewModel.drawCard(deck.deckId).observe(this){ card ->
                    val cardImage = ImageView(this)
                    cardImage.setImageBitmap(getCard(card.rank, card.suit))
                    addCardToLayout(scrollLayout, cardImage)
                    playerCards++
                }
            }

            jeuCarte = ImageView(this)
            jeuCarte.setImageResource(R.drawable.jeu_carte)
        }
    }

    private fun addCardToLayout(layout: LinearLayout, card: ImageView) {
        val cardNumber: Int = if(layout.id == dealerLayout.id){
            dealerCards
        }else{
            playerCards
        }

        card.x = 0f - (cardNumber * 120f)
        card.y = 0f

        layout.addView(card)
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
            "Trefle" -> 1
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
        return Bitmap.createBitmap(
            (jeuCarte.drawable as BitmapDrawable).bitmap,
            384,
            1117,
            192,
            279
        )
    }
}

