package com.example.black_jack

import android.annotation.SuppressLint
import android.graphics.Bitmap
import android.graphics.drawable.BitmapDrawable
import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.ViewModelProvider
import kotlin.math.round

class MainActivity : AppCompatActivity() {
    private lateinit var cardDeckImage: ImageView
    private lateinit var viewModel: MainViewModel

    private lateinit var dealerLayout: LinearLayout
    private lateinit var playerLayout: LinearLayout
    private lateinit var scrollLayout: LinearLayout
    private lateinit var btnHit: Button
    private lateinit var btnStand: Button

    @SuppressLint("SetTextI18n", "CutPasteId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val btnStats = findViewById<Button>(R.id.btnStats)
        btnHit = findViewById(R.id.btnHit)
        btnStand = findViewById(R.id.btnStand)

        cardDeckImage = ImageView(this)
        cardDeckImage.setImageResource(R.drawable.jeu_carte)

        viewModel = ViewModelProvider(this)[MainViewModel::class.java]

        dealerLayout = findViewById(R.id.dealerLayout)
        playerLayout = findViewById(R.id.playerLayout)
        scrollLayout = findViewById(R.id.playerLayout)

        viewModel.initDatabase()
        viewModel.initGame()
        btnHit.isEnabled = false
        btnStand.isEnabled = false

        viewModel.getDeck().observe(this){ deck ->
            Toast.makeText(this, "Deck id: ${deck.deckId}", Toast.LENGTH_SHORT).show()

            viewModel.bank.value?.let { it1 ->
                BankDialog.newInstance("Blackjack start, please bet", it1).show(supportFragmentManager, "bankDialog")
            }

            viewModel.inGame.observe(this){ inGame ->
                if (inGame) start(deck)
                else {
                    btnHit.isEnabled = false
                    btnStand.isEnabled = false
                }
            }

            btnHit.setOnClickListener {
                btnHit.isEnabled = false
                btnStand.isEnabled = false

                viewModel.drawCard(deck.deckId).observe(this){ card ->
                    viewModel.addPlayerCard(card)
                    btnHit.isEnabled = true
                    btnStand.isEnabled = true
                }
            }

            btnStand.setOnClickListener {
                btnHit.isEnabled = false
                btnStand.isEnabled = false

                stand(deck)
                //result(true)
            }
        }

        viewModel.getPlayerHand().observe(this){
            updatePlayerHand()
            updatePlayerCount()

            result()
        }

        viewModel.getDealerHand().observe(this){
            updateDealerHand()
            updateDealerCount()

            if (viewModel.getDealerHand().value?.size!! < 3){
                result()
            }
            else{
                result(true)
            }
        }

        btnStats.setOnClickListener {
            viewModel.setStatsVisible(true)
        }

        viewModel.bet.observe(this){
            findViewById<TextView>(R.id.txtBet).text = "$$it"
            Toast.makeText(this, "Bet: $it", Toast.LENGTH_SHORT).show()
        }
    }

    private fun start(deck: Deck) {
        viewModel.resetHands()
        btnHit.isEnabled = false
        btnStand.isEnabled = false

        viewModel.drawCard(deck.deckId).observe(this){ card1 ->
            viewModel.addPlayerCard(card1)
            viewModel.removeOneStat(card1.rank)

            viewModel.drawCard(deck.deckId).observe(this){ card2 ->
                card2.hidden = true
                viewModel.addDealerCard(card2)
                viewModel.removeOneStat(card2.rank)

                viewModel.drawCard(deck.deckId).observe(this){ card3 ->
                    viewModel.addPlayerCard(card3)
                    viewModel.removeOneStat(card3.rank)

                    viewModel.drawCard(deck.deckId).observe(this){ card4 ->
                        viewModel.addDealerCard(card4)
                        viewModel.removeOneStat(card4.rank)

                        if (viewModel.getPlayerValue() == 21){
                            updateDealerHand(true)
                            updateDealerCount()
                            result(true)
                        }

                        btnHit.isEnabled = true
                        btnStand.isEnabled = true
                    }
                }
            }
        }
    }

    private fun result(hasStand: Boolean = false){
        if (viewModel.inGame.value == false) return

        var hasStandReally = hasStand
        if (viewModel.getDealerValue() > 21) hasStandReally = true

        if (viewModel.getPlayerValue() == 21 && viewModel.getPlayerHand().value?.size == 2 && hasStand){
            if (viewModel.getDealerValue() != 21 && viewModel.getDealerHand().value?.size == 2){
                viewModel.inGame.value = false
                viewModel.bank.value = viewModel.bank.value?.plus(viewModel.bet.value!!)
                viewModel.bank.value?.let { bank -> BankDialog.newInstance("Black Jack!", bank).show(supportFragmentManager, "bankDialog") }
                return
            } else {
                viewModel.inGame.value = false
                viewModel.bank.value?.let { bank -> BankDialog.newInstance("Draw ! So sad after a Black Jack...", bank).show(supportFragmentManager, "bankDialog") }
                return
            }
        }

        if (viewModel.getPlayerValue() > 21){
            updateDealerHand(true)
            updateDealerCount()
            viewModel.inGame.value = false
            viewModel.bank.value = viewModel.bank.value?.minus(viewModel.bet.value!!)
            viewModel.bank.value?.let { bank -> BankDialog.newInstance("You've lost, you're over 21", bank).show(supportFragmentManager, "bankDialog") }
            return
        }

        else if (hasStandReally){
            if (viewModel.getDealerValue() > 21){
                viewModel.inGame.value = false
                viewModel.bank.value = viewModel.bank.value?.plus(viewModel.bet.value!!)
                viewModel.bank.value?.let { bank -> BankDialog.newInstance("You've won, dealer is over 21", bank).show(supportFragmentManager, "bankDialog") }
                return
            }

            else if (viewModel.getPlayerValue() < viewModel.getDealerValue()){
                viewModel.inGame.value = false
                viewModel.bank.value = viewModel.bank.value?.minus(viewModel.bet.value!!)
                viewModel.bank.value?.let { bank -> BankDialog.newInstance("You've lost, dealer is over you", bank).show(supportFragmentManager, "bankDialog") }
                return
            }

            else if (viewModel.getPlayerValue() == viewModel.getDealerValue()){
                viewModel.inGame.value = false
                viewModel.bank.value?.let { bank -> BankDialog.newInstance("Draw, you're equal to dealer", bank).show(supportFragmentManager, "bankDialog") }
                return
            }
        }
    }

    private fun stand(deck: Deck){
        updateDealerHand(true)
        updateDealerCount()

        if (viewModel.getDealerValue() < 17 || viewModel.getDealerValue() < viewModel.getPlayerValue()) {
            handleStand(deck)
        } else {
            updateDealerHand()
            updateDealerCount()
            result(true)
        }
    }

    private fun handleStand(deck: Deck){
        viewModel.drawCard(deck.deckId).observe(this){ card ->
            viewModel.addDealerCard(card)
            updateDealerHand()
            updateDealerCount()

            if (viewModel.getDealerValue() < 17 || viewModel.getDealerValue() < viewModel.getPlayerValue()) {
                handleStand(deck)
            }
        }
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
            if (reveal && card.hidden){
                card.hidden = false
                viewModel.removeOneStat(card.rank)
            }

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

        cardImage.x = 0f
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

