package com.example.black_jack

import android.graphics.Bitmap
import android.graphics.drawable.BitmapDrawable
import android.os.Bundle
import android.widget.ImageView
import android.widget.LinearLayout
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.ConstraintLayout
import kotlin.math.round


class MainActivity : AppCompatActivity() {
    lateinit var jeuCarte: ImageView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val mainLayout = findViewById<ConstraintLayout>(R.id.mainLayout)
        val subLayout = findViewById<LinearLayout>(R.id.subLayout)

        //create an imageview with jeu_carte.png
        jeuCarte = ImageView(this)
        jeuCarte.setImageResource(R.drawable.jeu_carte)

        val carte = ImageView(this)
        carte.setImageBitmap(getCover())
        carte.x = 0f
        carte.y = 0f
        subLayout.addView(carte)


/*
        mainLayout.addView(jeuCarte)

        jeuCarte.layoutParams.height = 200
        jeuCarte.layoutParams.width = 200
        jeuCarte.x = 300F
        jeuCarte.y = 500F*/
    }

    fun getCard(rank: String, suit: String): Bitmap {
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

    fun getCover(): Bitmap {
        val width = 192
        val height = 279.5
        return Bitmap.createBitmap(
            (jeuCarte.drawable as BitmapDrawable).bitmap,
            2 * width,
            round(4 * height).toInt(),
            width,
            round(height).toInt()
        )
    }
}

