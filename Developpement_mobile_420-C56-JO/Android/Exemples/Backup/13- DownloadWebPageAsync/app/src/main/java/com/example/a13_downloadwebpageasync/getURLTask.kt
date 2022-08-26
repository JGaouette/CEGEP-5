package com.example.a13_downloadwebpageasync

import android.os.AsyncTask
import android.util.Log
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStreamReader
import java.net.MalformedURLException
import java.net.URL


class getURLTask : AsyncTask< String, Void, String>() {


    interface AsyncResponse {
        fun processFinish(Output: String)
    }

    var ui: AsyncResponse? = null

    override fun doInBackground(vararg params: String): String {

        var reader : BufferedReader? = null
        var buffer : StringBuffer? = null

        try {

            val url = URL(params[0])
            val uc = url.openConnection()
            uc.connect()

            reader = BufferedReader(InputStreamReader(uc.getInputStream()))
            buffer = StringBuffer()

            // Nombre de caractère lu
            val chars = CharArray(1024)

            reader.use {
                it.read(chars)
                buffer.append(chars, 0, chars.size)
            }

            reader.close()

            return buffer!!.toString()
        }
        catch (e: MalformedURLException){
            Log.d("getURL", "Malformed URL")
        }
        catch (e: IOException){
            Log.d("getURL", e.toString())
        }
        catch (e: Exception){
            Log.d("getURL", e.toString())
        }


        return ""

    }

    override fun onPostExecute (result:String){
        ui?.processFinish(result)
    }

}