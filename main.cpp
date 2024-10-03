 /************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Main Function                                 *
     * Date:  2/20/24                                        *
*************************************************************/


#include "stdafx.h"
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Round.h"
#include "Computer.h"
#include "Tournament.h"
using namespace std;




//Game Loop functions used in this file
void mainGameLoop(Board& gameBoard);
void importedGameLoop(Board& gameBoard);


/* *********************************************************************
Function Name: main
Purpose: The main function to start the Lines of Action game and initiate game flow.

Parameters:
    None

Return: 
    An integer representing the exit status.

Algorithm:
    1. Initialize a Board object to represent the game board.
    2. Prompt the user to choose an action:
        a. If the user chooses to start a new game:
            i. Display a message indicating the start of a new game.
            ii. Display the initial state of the board.
            iii. Call the mainGameLoop() function to execute the game loop for a new game.
        b. If the user chooses to import a game from a file:
            i. Prompt the user for the file name to import.
            ii. If the board is successfully loaded from the file:
                - Display a message indicating the successful recovery of the game board.
                - Display the current state of the board.
                - Call the importedGameLoop() function to execute the game loop for the imported game.
            iii. If the board cannot be loaded from the file:
                - Display an error message.
                - Exit the program with a return value of -1.
        c. If the user chooses to exit the program:
            - Exit the program with a return value of 0.

Reference: None
********************************************************************* */
int main()
{
    //GAME BOARD INITIALIZATION

    Board gameBoard; //board object
    
    int userChoice = 0; //user input (for first menu)
    
    string userBoard = " "; //string to hold imported board file name

    //User Initial action and input validation
    cout << "\n\nWelcome to Lines of Action! Would you like to... \n1) Start a new game\n2) Import a game from file\n3) Exit Program\n" << endl;
    cin >> userChoice;

    //Determine action taken based on user input
    if(userChoice == 1)
    {
        //If 1, start new game
        cout << "\nGreat, let's start a new game!\n";
        cout << "\nBoard's initial state:\n";
        gameBoard.displayBoard();
        mainGameLoop(gameBoard);
    }
    else if(userChoice == 2)
    {
        //If 2, import game board (or exit program if it fails)
        cout << "\nOk, let's import the board from a file. What is the file name?: ";
        cin >> userBoard;
        if(gameBoard.loadFromFile(userBoard))
        {
            cout << "\nGame Board Recovered. Time to play!" << endl;
            gameBoard.displayBoard();
            importedGameLoop(gameBoard);
        }
        else
        {
            cout << "\nSorry, the game board could not be recovered. The program will now close.\n";
            return -1;
        }
        

    }
    else
    {
        //If 3 or anything else, close program
        return 0;
    }
    


    cout << "\n\nThank you for playing Lines of Action! Have a great day!\n" << endl;

    return 0;
}



/* *********************************************************************
Function Name: mainGameLoop
Purpose: To execute the regular game loop when starting a new game without importing a board.

Parameters:
    1. gameBoard: A reference to a Board object representing the game board.

Return: 
    None

Algorithm:
    1. Perform a coin toss to decide which player plays first:
        a. Prompt the user to input their choice for the coin toss (0 for heads, 1 for tails).
        b. Validate the user input to ensure it's either 0 or 1.
        c. Generate a random number (0 or 1) as the result of the coin toss.
    2. Based on the coin toss result:
        a. If the result matches the user's choice:
            i. Display a message indicating that the human player wins the coin toss and will play first as Black.
            ii. Initialize a Human player as player 1 with color 'B'.
            iii. Initialize a Computer player as player 2 with color 'W'.
        b. If the result doesn't match the user's choice:
            i. Display a message indicating that the computer player wins the coin toss and will play first as Black.
            ii. Initialize a Computer player as player 1 with color 'B'.
            iii. Initialize a Human player as player 2 with color 'W'.
    3. Set up and start the tournament with the initialized players:
        a. Create a Tournament object with player 1 and player 2.
        b. Call the startTournament() function of the Tournament object to begin the game.

Reference: None
********************************************************************* */
void mainGameLoop(Board& gameBoard)
{
    //COIN TOSS / PLAYER INITIALIZATION
    
    // Perform the coin toss to decide who plays first
    cout << "\nPerforming coin toss to decide who plays first...\n";

    int userCoin = -1;
    // Ask the user for the result of the coin toss 
    cout << "Enter your choice for the coin toss (0 for heads, 1 for tails): ";
    cin >> userCoin;
    while (userCoin != 0 && userCoin != 1) {
        cout << "\nInvalid input. Please enter 0 for heads or 1 for tails: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> userCoin;
    }

    srand(time(NULL)); // Seed the random number generator
    int tossResult = rand() % 2; // Generate a random number (0 or 1) for the coin toss



    // GAME LOOP BASED ON TOSS
    if (tossResult == userCoin)
    {
        cout << "\nHuman player wins the coin toss! Human player will play first as Black.\n\n";
        Human player1('B');
        Computer player2('W');
        // Create a Tournament object
        Tournament tournament(player1, player2); 

        // Start the tournament
        tournament.startTournament(gameBoard);
    }
    else
    {
        cout << "\nComputer player wins the coin toss! Computer player will play first as Black.\n\n";
        Computer player1('B');
        Human player2('W');
        // Create a Tournament object
        Tournament tournament(player1, player2);

        // Start the tournament
        tournament.startTournament(gameBoard);
    }
    
}



/* *********************************************************************
Function Name: importedGameLoop
Purpose: To execute the game loop when importing a board from a file and starting from a specific state.

Parameters:
    1. gameBoard: A reference to a Board object representing the game board.

Return: 
    None

Algorithm:
    1. Prompt the user to input the number of rounds won by the human player:
        a. Validate the input to ensure it's a non-negative integer less than 10.
    2. Prompt the user to input the number of rounds won by the computer player:
        a. Validate the input to ensure it's a non-negative integer less than 10.
    3. Prompt the user to input the next player:
        a. Validate the input to ensure it's either 1 or 2.
    4. Prompt the user to input the color of the next player:
        a. Validate the input to ensure it's either 'W' or 'B'.
    5. Based on the input parameters:
        a. If the next player is Human and their color is Black:
            i. Initialize a Human player as player 1 with color 'B' and set their number of wins.
            ii. Initialize a Computer player as player 2 with color 'W' and set their number of wins.
        b. If the next player is Human and their color is White:
            i. Initialize a Human player as player 1 with color 'W' and set their number of wins.
            ii. Initialize a Computer player as player 2 with color 'B' and set their number of wins.
        c. If the next player is Computer and their color is Black:
            i. Initialize a Computer player as player 1 with color 'B' and set their number of wins.
            ii. Initialize a Human player as player 2 with color 'W' and set their number of wins.
        d. If the next player is Computer and their color is White:
            i. Initialize a Computer player as player 1 with color 'W' and set their number of wins.
            ii. Initialize a Human player as player 2 with color 'B' and set their number of wins.
        e. If the input parameters are invalid, display an error message.
    6. Set up and start the tournament with the initialized players:
        a. Create a Tournament object with player 1 and player 2.
        b. Call the startTournament() method of the Tournament object to begin the game.

Reference: ChatGPT wrote code for input validations for the first 4 variables
********************************************************************* */
void importedGameLoop(Board& gameBoard)
{
    int humanRounds;
    int computerRounds;
    int nextPlayer;
    char nextPlayerColor;

    // Prompt and get valid input for number of rounds won by human
    cout << "\nHow many rounds has the human won?: ";
    cin >> humanRounds;
    while (cin.fail() || humanRounds < 0 || humanRounds > 10) {
        cout << "Invalid input. Please enter a non-negative integer less than 10: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> humanRounds;
    }

    // Prompt and get valid input for number of rounds won by computer
    cout << "\nHow many rounds has the computer won?: ";
    cin >> computerRounds;
    while (cin.fail() || computerRounds < 0 || computerRounds > 10) {
        cout << "Invalid input. Please enter a non-negative integer less than 10: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> computerRounds;
    }

    // Prompt and get valid input for the next player
    cout << "\nWho is the next Player?\n\n1) Human\n2) Computer\n";
    cin >> nextPlayer;
    while (cin.fail() || (nextPlayer != 1 && nextPlayer != 2)) {
        cout << "Invalid input. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> nextPlayer;
    }

    // Prompt and get valid input for the next player's color
    cout << "\nWhat color is the next player? (enter W/B): ";
    cin >> nextPlayerColor;
    while (cin.fail() || (nextPlayerColor != 'W' && nextPlayerColor != 'B')) {
        cout << "Invalid input. Please enter W or B: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> nextPlayerColor;
    }



    if (nextPlayer == 1 && nextPlayerColor == 'B')
    {
        Human player1('B');
        player1.setWins(humanRounds);
        Computer player2('W');
        player2.setWins(computerRounds);
        // Create a Tournament object
        Tournament tournament(player1, player2);

        // Start the tournament
        tournament.startTournament(gameBoard);
    }
    else if(nextPlayer == 1 && nextPlayerColor == 'W')
    {
        Human player1('W');
        player1.setWins(humanRounds);
        Computer player2('B');
        player2.setWins(computerRounds);
        // Create a Tournament object
        Tournament tournament(player1, player2);

        // Start the tournament
        tournament.startTournament(gameBoard);
    }
    else if(nextPlayer == 2 && nextPlayerColor == 'B')
    {
        Computer player1('B');
        player1.setWins(computerRounds);
        Human player2('W');
        player2.setWins(humanRounds);
        // Create a Tournament object
        Tournament tournament(player1, player2);

        // Start the tournament
        tournament.startTournament(gameBoard);
    }
    else if (nextPlayer == 2 && nextPlayerColor == 'W'){
        Computer player1('W');
        player1.setWins(computerRounds);
        Human player2('B');
        player2.setWins(humanRounds);
        // Create a Tournament object
        Tournament tournament(player1, player2);

        // Start the tournament
        tournament.startTournament(gameBoard);
    }
    else{
        cerr << "\nError in input parameters" << endl;
    }

}


