package com.example.black_jack

import android.graphics.Bitmap
import android.graphics.drawable.BitmapDrawable
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.LiveData
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.findNavController
import kotlin.math.round


class MainActivity : AppCompatActivity() {
    private lateinit var cardDeckImage: ImageView
    private lateinit var viewModel: MainViewModel

    private lateinit var dealerLayout: LinearLayout
    private lateinit var playerLayout: LinearLayout
    private lateinit var scrollLayout: LinearLayout

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val btnHit = findViewById<Button>(R.id.btnHit)
        val btnStand = findViewById<Button>(R.id.btnStand)
        val btnStats = findViewById<Button>(R.id.btnStats)

        cardDeckImage = ImageView(this)
        cardDeckImage.setImageResource(R.drawable.jeu_carte)

        viewModel = ViewModelProvider(this)[MainViewModel::class.java]

        dealerLayout = findViewById(R.id.dealerLayout)
        playerLayout = findViewById(R.id.playerLayout)
        scrollLayout = findViewById(R.id.playerLayout)

        viewModel.resetStats()

        viewModel.getDeck().observe(this){ deck ->
            Toast.makeText(this, "Deck id: ${deck.deckId}", Toast.LENGTH_SHORT).show()

            viewModel.drawCard(deck.deckId).observe(this){ card ->
                viewModel.addPlayerCard(card)
            }

            viewModel.drawCard(deck.deckId).observe(this){ card ->
                card.hidden = true
                viewModel.addDealerCard(card)
            }

            viewModel.drawCard(deck.deckId).observe(this){ card ->
                viewModel.addPlayerCard(card)
            }

            viewModel.drawCard(deck.deckId).observe(this){ card ->
                viewModel.addDealerCard(card)
            }

            btnHit.setOnClickListener {
                viewModel.drawCard(deck.deckId).observe(this){ card ->
                    viewModel.addPlayerCard(card)
                }
            }

            btnStand.setOnClickListener {
                stand(deck)
                result()

            }
        }

        viewModel.getPlayerHand().observe(this){
            updatePlayerHand()
            updatePlayerCount()

            if (viewModel.getPlayerValue() > 21) {
                Toast.makeText(this, "Player lose", Toast.LENGTH_SHORT).show()
                /*
                btnHit.isEnabled = false
                btnStand.isEnabled = false
                */
            }
        }

        viewModel.getDealerHand().observe(this){
            updateDealerHand()
            updateDealerCount()

            if (viewModel.getDealerValue() > 21) {
                Toast.makeText(this, "Player win", Toast.LENGTH_SHORT).show()
            }
        }

        btnStats.setOnClickListener {
            //viewModel.setStatsVisible(true)
            //create a list with viewModel.getStats()
            val stats : List<Stats> = viewModel.getAllStats()

            Toast.makeText(this, "Stats are visible", Toast.LENGTH_SHORT).show()
        }
    }

    private fun result(){
        updateDealerHand(true)
        updateDealerCount()

        if (viewModel.getPlayerValue() > viewModel.getDealerValue()) {
            Toast.makeText(this, "Player win", Toast.LENGTH_SHORT).show()
        } else if (viewModel.getPlayerValue() < viewModel.getDealerValue()) {
            Toast.makeText(this, "Player lose", Toast.LENGTH_SHORT).show()
        } else {
            Toast.makeText(this, "Draw", Toast.LENGTH_SHORT).show()
        }
    }

    private fun stand(deck: Deck){
        updateDealerHand(true)
        updateDealerCount()

        if (viewModel.getDealerValue() < 17 || viewModel.getDealerValue() < viewModel.getPlayerValue()) {
            viewModel.drawCard(deck.deckId).observe(this){ card ->
                viewModel.addDealerCard(card)
                updateDealerHand()
                updateDealerCount()

                if (viewModel.getDealerValue() < 17 || viewModel.getDealerValue() < viewModel.getPlayerValue()) {
                    stand(deck)
                }
            }
        }

        Toast.makeText(this, "Dealer has finished drawing cards", Toast.LENGTH_SHORT).show()
    }

    private fun updatePlayerHand(){
        playerLayout.removeAllViews()
        viewModel.getPlayerHand().value?.forEach{
            addCardToLayout(playerLayout, it)
        }
    }

    private fun updateDealerHand(reveal : Boolean = false){
        dealerLayout.removeAllViews()
        viewModel.getDealerHand().value?.forEach{ card ->
            if (reveal && card.hidden) card.hidden = false

            addCardToLayout(dealerLayout, card)
        }
    }

    private fun updatePlayerCount() {
        val txtPlayerCount = findViewById<TextView>(R.id.txtPlayerCount)
        txtPlayerCount.text = viewModel.getPlayerValue().toString()
    }

    private fun updateDealerCount() {
        val txtDealerCount = findViewById<TextView>(R.id.txtDealerCount)
        txtDealerCount.text = viewModel.getDealerValue().toString()
    }


    private fun addCardToLayout(layout: LinearLayout, card: Card) {
        val cardImage = ImageView(this)

        if (card.hidden) {
            cardImage.setImageBitmap(getCover())
        } else {
            cardImage.setImageBitmap(getCardImage(card))
        }

        val cardNumber: Int = if(layout.id == dealerLayout.id){
            viewModel.getDealerCardCount()
        }else{
            viewModel.getPlayerCardCount()
        }

        cardImage.x = 0f /* - (cardNumber * 30f) */
        cardImage.y = 0f

        layout.addView(cardImage)
    }

    private fun getCardImage(card: Card): Bitmap {
        val col: Int = when (card.rank) {
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
        val row: Int = when (card.suit) {
            "Trefle" -> 1
            "Carreau" -> 2
            "Coeur" -> 3
            "Pique" -> 4
            else -> 0
        }
        val offset: Int = when (card.rank) {
            "As" -> 0
            else -> 1
        }

        val width = 192
        val height = 279.5
        return Bitmap.createBitmap(
            (cardDeckImage.drawable as BitmapDrawable).bitmap,
            (col - 1) * width + offset,
            round((row - 1) * height).toInt(),
            width,
            round(height).toInt()
        )
    }

    private fun getCover(): Bitmap {
        return Bitmap.createBitmap(
            (cardDeckImage.drawable as BitmapDrawable).bitmap,
            384,
            1117,
            192,
            279
        )
    }
}

