/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Tournament.cpp   (Tournament Class)           *
     * Date:  2/20/24                                        *
*************************************************************/


#include "Tournament.h"

Tournament::Tournament(Player& player1, Player& player2) : player1(player1), player2(player2) {}


Tournament::~Tournament() {}



/* *********************************************************************
Function Name: startTournament
Purpose: Start the tournament by playing rounds until the player decides to stop.

Parameters:
    gameBoard (Board&): A reference to the game board.

Return: 
    void

Algorithm: 
    1. Initialize a Round object.
    2. Create a loop to play rounds until the player decides to stop:
        a. Call the playRound() function to play a round.
        b. Prompt the player if they want to play another round.
        c. If the player chooses to play another round (by entering 'Y' or 'y'), start new round; otherwise, exit the loop.
    3. Announce the winner of the tournament.

Reference: None
********************************************************************* */
void Tournament::startTournament(Board& gameBoard) {
    Round round;
    char playAnotherRound;
    do {
        playRound(gameBoard);
        cout << "Do you want to play another round? (Y/N): ";
        cin >> playAnotherRound;
        if(toupper(playAnotherRound) != 'Y') break;
        gameBoard.initializeBoard();
        cout << "\nNew Round! Board's initial state:\n";
        gameBoard.displayBoard();
    } while (toupper(playAnotherRound) == 'Y');
    announceWinner();
}



/* *********************************************************************
Function Name: playRound
Purpose: Play a round of the tournament.

Parameters:
    gameBoard (Board&): A reference to the game board.

Return: 
    void

Algorithm: 
    1. Initialize a Round object.
    2. Create a loop to continue playing the round until the game is over:
        a. Let Player 1 take action by calling the playerAction() function of player1.
        b. Check if Player 1 is the winner using the isWinner() function of player1:
            i. If Player 1 is the winner, announce "Player 1 wins!", increase Player 1's win count using the increaseWin() function of player1,
               set the game over state of the round to true using the setGameOver() function of round, and exit the loop.
        c. Check if the round is over after Player 1's turn:
            i. If the round is over, exit the loop.
        d. Let Player 2 take action by calling the playerAction() function of player2.
        e. Check if Player 2 is the winner using the isWinner() function of player2:
            i. If Player 2 is the winner, announce "Player 2 wins!", increase Player 2's win count using the increaseWin() function of player2,
               set the game over state of the round to true using the setGameOver() function of round, and exit the loop.

Reference: None
********************************************************************* */
void Tournament::playRound(Board& gameBoard) {
    Round round;
    while (!round.isGameOver()) {
        player1.playerAction(gameBoard, round);
        if (player1.isWinner(gameBoard)) {
            cout << "Player 1 wins!" << endl;
            player1.increaseWin();
            round.setGameOver(true);
            break;
        }
        if (round.isGameOver()) break;
        player2.playerAction(gameBoard, round);
        if (player2.isWinner(gameBoard)) {
            cout << "Player 2 wins!" << endl;
            player2.increaseWin();
            round.setGameOver(true);
            break;
        }
    }
}



/* *********************************************************************
Function Name: announceWinner
Purpose: Announce the winner of the tournament based on the number of wins of each player.

Return: 
    void

Algorithm: 
    1. Get the number of wins for Player 1 using the getWins() method of player1.
    2. Get the number of wins for Player 2 using the getWins() method of player2.
    3. Print "Tournament over! " to indicate the end of the tournament.
    4. Compare the number of wins for Player 1 and Player 2:
        a. If Player 1 has more wins than Player 2, announce "Player 1 wins the tournament with [number of wins] wins!".
        b. If Player 2 has more wins than Player 1, announce "Player 2 wins the tournament with [number of wins] wins!".
        c. If both players have the same number of wins, announce "The tournament ends in a draw with [number of wins] wins each!".

Reference: None
********************************************************************* */
void Tournament::announceWinner() {
    int player1Wins = player1.getWins();
    int player2Wins = player2.getWins();
    cout << "Tournament over! ";
    if (player1Wins > player2Wins) {
        cout << "Player 1 wins the tournament with " << player1Wins << " wins!" << endl;
    } else if (player2Wins > player1Wins) {
        cout << "Player 2 wins the tournament with " << player2Wins << " wins!" << endl;
    } else {
        cout << "The tournament ends in a draw with " << player1Wins << " wins each!" << endl;
    }
}
