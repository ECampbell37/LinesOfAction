/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Human.cpp   (Human Class)                     *
     * Date:  2/20/24                                        *
*************************************************************/


#include "Human.h"
#include "Board.h"
#include "Computer.h"

// Constructor 
Human::Human(char color) : Player(color) {}

// Destructor
Human::~Human() {}


/* *********************************************************************
Function Name: playerAction
Purpose: Perform an action based on the user's choice.

Parameters:
    board (Board&): A reference to the game board.
    round (Round&): A reference to the current round of the game.

Return: 
    void

Algorithm: 
    1. Display the menu of options for the user to choose from.
    2. Read the user's choice from the standard input.
    3. Validate the user's choice and repeatedly prompt the user until a valid choice is made.
    4. Execute the corresponding action based on the user's choice:
        a. Make a move: Execute the move by calling the executeMove() function.
        b. Ask for help: Request help from the Computer Class
        c. Save the game and exit: Prompt the user to enter a file name to save the game state to.
           If the file saving is successful, set the game over status of the current round to true.
        d. Exit without saving: Set the game over status of the current round to true.
    5. If the user enters an invalid choice, display an error message.


Note: This function is inherited by the Player class for polymorphic behavior

Reference: ChatGPT helped specifically with input validation on the file (.txt extension and no spaces)
********************************************************************* */
void Human::playerAction(Board& board, Round& round)
{
    int playerChoice = 0;
    string userFile = "default.txt";

    cout << "\nWhat would you like to do?\n1) Make a Move\n2) Ask for help\n3) Save the game and exit\n4) Exit without saving\n";
    cin >> playerChoice;

    while(playerChoice != 1 && playerChoice != 2 && playerChoice != 3 && playerChoice != 4)
    {
        cout << "\nPlease select one of the four options (type 1, 2, 3, or 4): ";

        // Ignore remaining characters in the buffer, up to the maximum buffer size
        cin.clear();
        cin.ignore(INT_MAX, '\n');

        // Try to read playerChoice again
        cin >> playerChoice;
    }

    switch(playerChoice)
    {
        case 1:
            executeMove(board);
            break;
        case 2:
            cout << "\nHelp Requested\n";
            {
                Computer helper(this->getColor());
                helper.provideMoveRecommendation(board, this->getColor());
            }
            executeMove(board);
            break;
        case 3:
            cout << "\nType the file name you would like to save to: \n";
            cin >> userFile;

            // Validate the file name (non empty, no spaces, has .txt extension)
            while (userFile.empty() || userFile.find(' ') != string::npos || userFile.substr(userFile.find_last_of(".") + 1) != "txt") {
                cerr << "\nError: Invalid file name format. Please enter a valid file name (without spaces) with .txt extension: ";
                cin.clear(); // Clear the input buffer
                cin.ignore(INT_MAX, '\n'); // Ignore remaining characters in the buffer
                cin >> userFile;
            }

            if(!board.saveToFile(userFile))
            {
                cerr << "\nError with file generation...\n";
            }
            else
            {
                round.setGameOver(true);
            }
            break;
        case 4:
            round.setGameOver(true);
            break;
        default:
            cout << "\nError, invalid input\n";
    }
}



/* *********************************************************************
Function Name: executeMove
Purpose: Perform a move for the human player.

Parameters:
    board (Board&): A reference to the game board.

Return: 
    void

Algorithm: 
    1. Prompt the user to enter their move in the format "source square destination square" (e.g., "A1 B2").
    2. Read the source and destination squares from the standard input.
    3. Translate the source and destination squares into numeric indices using the inputTranslator() function.
    4. Validate the move using the board's validateMove() method. If the move is not valid, repeatedly prompt the user to enter a valid move.
    5. Output the human player's move to the screen.
    6. Update the game state with the move by calling the board's updateBoard() method.
    7. Display the updated game board using the displayBoard() method.

Reference: None
********************************************************************* */
void Human::executeMove(Board& board) {
    cout << "Enter your move (source square followed by destination square, e.g., A1 B2): ";
    
    // Read user input for the source and destination squares
    string source, destination;
    cin >> source >> destination;

    //Translate Move into numeric array
    inputTranslator(source, destination, move);

    //Move Validation
    while(!board.validateMove(move[0], move[1], move[2], move[3], this->getColor()))
    {
        cout << "\nPlease enter a valid move: ";
        cin >> source >> destination;
        inputTranslator(source, destination, move);
    }


    // Output the move to the screen
    cout << "\n\nHuman player's move: " << source << " -> " << destination << endl;


    // Update the game state with the move
    cout << "Updating game state..." << endl;

    board.updateBoard(move[0], move[1], move[2], move[3], this->getColor());
    board.displayBoard();

}
