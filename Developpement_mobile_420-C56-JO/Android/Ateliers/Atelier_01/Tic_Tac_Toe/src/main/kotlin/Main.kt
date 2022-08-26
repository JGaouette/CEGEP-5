import com.sun.jdi.IntegerValue
import java.io.Console
import java.lang.NumberFormatException

var board: Array<String> = arrayOf("00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15")

fun main() {
    var turn = 0
    var win = false
    var player: Array<String> = arrayOf("X ", "O ")

    while (!win){
        println("════════════════════")
        println("It is the turn of " + player[turn % 2])
        println("")

        println("  " + board[0] + " ║ " + board[1] + " ║ " + board[2] + " ║ " + board[3] + "  ")
        println("═════╬════╬════╬═════")
        println("  " + board[4] + " ║ " + board[5] + " ║ " + board[6] + " ║ " + board[7] + "  ")
        println("═════╬════╬════╬═════")
        println("  " + board[8] + " ║ " + board[9] + " ║ " + board[10] + " ║ " + board[11] + "  ")
        println("═════╬════╬════╬═════")
        println("  " + board[12] + " ║ " + board[13] + " ║ " + board[14] + " ║ " + board[15] + "  ")
        println("")

        var isGood = false
        while(!isGood){
            try {
                println("Wich case do you play in?")

                var read = readLine()
                var answer = read!!.toInt()
                if(board[answer] != "X " && board[answer] != "O ") {
                    board[answer] = player[turn % 2]
                    isGood = true
                }
            }
            catch (e: NumberFormatException){}
            catch (e: ArrayIndexOutOfBoundsException){}
        }

        turn++

        if(turn > 3){
            for (i in 0..12) {
                if (i == 0){
                    if(board[0] == board[5] && board[5] == board[10] && board[10] == board[15]) {
                        win = true
                        println(player[(turn - 1) % 2] + "is the winner!")
                    }
                }
                if (i == 3){
                    if(board[3] == board[6] && board[6] == board[9] && board[9] == board[12]) {
                        win = true
                        println(player[(turn - 1) % 2] + "is the winner!")
                    }
                }
                if (i < 4){
                    if(board[i] == board[i + 4] && board[i + 4] == board[i + 8] && board[i + 8] == board[i + 12]) {
                        win = true
                        println(player[(turn - 1) % 2] + "is the winner!")
                    }
                }
                if (i % 4 == 0){
                    if(board[i] == board[i + 1] && board[i + 1] == board[i + 2] && board[i + 2] == board[i + 3]) {
                        win = true
                        println(player[(turn - 1) % 2] + "is the winner!")
                    }
                }
            }
            if(turn == 16){
                win = true
                println("It is a draw")
            }
        }
    }
}
