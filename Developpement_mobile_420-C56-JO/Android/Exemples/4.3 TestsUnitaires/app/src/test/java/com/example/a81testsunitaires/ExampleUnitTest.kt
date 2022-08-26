package com.example.a81testsunitaires

import org.junit.Test

import org.junit.Assert.*

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
class MathUnitTest {
    @Test
    fun PGCDisCorrect() {
        val math = Math ("40", "50")
        val data = math.PGCD()
        assertEquals(15, data)
    }
}