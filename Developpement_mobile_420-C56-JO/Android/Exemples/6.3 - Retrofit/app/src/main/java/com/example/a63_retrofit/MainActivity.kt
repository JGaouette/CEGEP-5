package com.example.a63_retrofit

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.google.gson.GsonBuilder
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class MainActivity : AppCompatActivity(), Callback<List<Todo?>?> {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val retrofit = Retrofit.Builder()
            .baseUrl("https://jsonplaceholder.typicode.com/")
            .addConverterFactory(GsonConverterFactory.create())
            .build().create(API::class.java)

        val todo = Todo( 15, 101, "Essai", false )
        var todoCall = retrofit.addTodos(todo)

        todoCall.enqueue(object: Callback<Todo?>{
            override fun onResponse(call: Call<Todo?>, response: Response<Todo?>) {

                val todoResponse = response.body()!!
                Log.w("a63 / ADD", todoResponse.toString())
            }

            override fun onFailure(call: Call<Todo?>, t: Throwable) {
                TODO("Not yet implemented")
            }
        })

        var todosCall = retrofit.getTodos()
        todosCall?.enqueue(this)

        todosCall = retrofit.getTodosByUserId("15")
        todosCall?.enqueue(this)

    }

    override fun onResponse(call: Call<List<Todo?>?>, response: Response<List<Todo?>?>) {
        Log.d("a63", "onResponse: call: " + call.request().url());
        if (response.code() == 200) {
            val todoResponse = response.body()!!
            todoResponse.forEach {
                Log.w("a63 / LIST", it.toString())
            }
        }
    }

    override fun onFailure(call: Call<List<Todo?>?>, t: Throwable) {
        TODO("Not yet implemented")
    }

}


