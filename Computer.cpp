/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Computer.cpp   (Computer Class)               *
     * Date:  2/20/24                                        *
*************************************************************/


#include "Computer.h"

// Constructor
Computer::Computer(char color) : Player(color) {}

// Destructor
Computer::~Computer() {}



//Function for the computer player's action when it's their turn (starts chain of functions)
/* *********************************************************************
Function Name: playerAction
Purpose: To perform the computer player's action when it's their turn.

Parameters:
    1. board: A reference to a Board object representing the current game board.
    2. round: A reference to a Round object representing the current round of the game.

Return: 
    None

Algorithm:
    1. Call the selectBestMove function to choose and execute the best move based on evaluation criteria.

Note: This function is inherited by the Player class for polymorphic behavior

Reference: None
********************************************************************* */
void Computer::playerAction(Board& board, Round& round)
{
    selectBestMove(board, this->getColor());
}


// Function to choose the best move based on some criteria
/* *********************************************************************
Function Name: selectBestMove
Purpose: To choose the best move based on evaluation criteria and execute it.

Parameters:
    1. board: A reference to a Board object representing the current game board.
    2. currentPlayer: A character representing the color of the current player.

Return: 
    None

Algorithm:
    1. Generate all possible legal moves for the computer player.
    2. Evaluate the moves and find the index of the best move.
    3. If no valid moves were found, print a message and return.
    4. Get the coordinates of the best move.
    5. Execute the best move and display the updated game state.

Reference: None
********************************************************************* */
void Computer::selectBestMove(Board& board, char currentPlayer){
    // Generate all possible legal moves for the computer player
    generatePossibleMoves(board, currentPlayer);



    cout << "\nPossible Computer Moves:\n";
    for (int i = 0; i < possibleMoves.size(); i++) {
        int startRow = possibleMoves[i][0];
        int startCol = possibleMoves[i][1];
        int endRow = possibleMoves[i][2];
        int endCol = possibleMoves[i][3];
        string moveTranslated = reverseMoveTranslator(board, startRow, startCol, endRow, endCol);
        cout << "Move " << (i + 1) << ": " << moveTranslated << endl;
    }

    // Evaluate the moves and find the index of the best move
    int bestMoveIndex = evaluateMoves(board, possibleMoves, currentPlayer);

    // If no valid moves were found, return
    if (bestMoveIndex == -1) {
        cout << "No valid moves found." << endl;
        return;
    }

    // Get the coordinates of the best move
    int startRow = possibleMoves[bestMoveIndex][0];
    int startCol = possibleMoves[bestMoveIndex][1];
    int endRow = possibleMoves[bestMoveIndex][2];
    int endCol = possibleMoves[bestMoveIndex][3];

    // Execute the best move
    executeMove(board, startRow, startCol, endRow, endCol, currentPlayer, true);
}


// Function to generate all possible legal moves for the computer player
/* *********************************************************************
Function Name: generatePossibleMoves
Purpose: Generate all possible legal moves for the computer player.
   This function finds all legal moves that the computer player can make on the given board.

Parameters:
    board (Board&): A reference to the game board object passed by reference. This parameter represents the game board on which the moves are generated.
    currentPlayer (char): The character representing the current player. It indicates which player's pieces to search for on the board.

Return Value: 
    None. However, the function populates the class member variable 'possibleMoves' with the generated legal moves.

Algorithm: 
    1. Clear the vector 'possibleMoves' to remove any previous entries.
    2. Iterate through each space of the board.
    3. For each space containing a piece belonging to the current player:
        a. Iterate through the entire board.
        b. Check if the move from the current space to every other space on the board is valid using 'cpuMoveCheck' function.
        c. If the move is valid, add it to the list of possible moves.

Reference: None
********************************************************************* */
void Computer::generatePossibleMoves(Board& board, char currentPlayer) {
    possibleMoves.clear(); // Clear the vector of possible moves

    // Iterate through the board to find pieces belonging to the computer player
    for (int row = 0; row < board.getBoardSize(); row++) {
        for (int col = 0; col < board.getBoardSize(); col++) {
            if (board.getPiece(row, col) == currentPlayer) {
                // Check all adjacent squares for possible moves
                for (int r = 0; r < board.getBoardSize(); r++) {
                    for (int c = 0; c < board.getBoardSize(); c++) {
                        // Validate the move using cpuMoveCheck()
                        if (board.cpuMoveCheck(row, col, r, c, currentPlayer)) {
                            // Add the move to the list of possible moves
                            possibleMoves.push_back({row, col, r, c});
                        }
                    }
                }
            }
        }
    }
}


//Function to evaluate the utility of possible moves
/* *********************************************************************
Function Name: evaluateMoves
Purpose: To evaluate the utility of possible moves for the computer player.

Parameters:
    1. board: A constant reference to the Board object representing the current state of the game board.
    2. possibleMoves: A constant reference to a vector of vectors of integers representing the possible moves.
    3. currentPlayer: A character representing the current player ('B' for Black, 'W' for White).

Return: 
    int - The index of the best move in the vector of possible moves.

Algorithm:
    1. Initialize the best score to the lowest possible value and the index of the best move to -1.
    2. Iterate through all possible moves:
        a. Get the connectedness of the player's pieces before the move.
        b. Simulate the move on a temporary board object.
        c. Get the connectedness of the player's pieces after the move.
        d. Calculate the change in connectedness caused by the move.
        e. Calculate the score for this move based on the change in connectedness and center distance (less distance better).
        f. Update the best score and the index of the best move if this move has a higher score.
    3. Return the index of the best move.

Reference: None
********************************************************************* */
int Computer::evaluateMoves(const Board& board, const vector<vector<int>>& possibleMoves, char currentPlayer) {
    int bestScore = INT_MIN; // Initialize the best score to the lowest possible value
    int bestMoveIndex = -1; // Initialize the index of the best move

    // Iterate through all possible moves
    for (int i = 0; i < possibleMoves.size(); ++i) {
        // Get the connectedness of player's pieces before the move
        int initialConnectedness = this->calcConnectedPieces(board);

        // Simulate the move on a temporary board object
        Board tempBoard = board; // Create a copy of the original board
        executeMove(tempBoard, possibleMoves[i][0], possibleMoves[i][1], possibleMoves[i][2], possibleMoves[i][3], currentPlayer, false); // Make the move on the temporary board

        // Get the connectedness of player's pieces after the move
        int finalConnectedness = this->calcConnectedPieces(tempBoard);

        // Calculate the change in connectedness caused by the move
        int connectednessChange = finalConnectedness - initialConnectedness;

        // Calculate the score for this move based on the change in connectedness and center distance
        int moveScore = (2 * connectednessChange) + calculateDistanceToCenterScore(possibleMoves[i][2], 
                        possibleMoves[i][3], tempBoard.getBoardSize()); 

        // Check if this move has a higher score than the current best move
        if (moveScore > bestScore) {
            bestScore = moveScore; // Update the best score
            bestMoveIndex = i; // Update the index of the best move
        }
    }

    // Return the index of the best move
    return bestMoveIndex;
}


//Function to execute a move on a given board and update it
/* *********************************************************************
Function Name: executeMove
Purpose: To execute a move on a given board and update it.

Parameters:
    1. exBoard: A reference to the Board object representing the current state of the board being executed on (could be theoretical).
    2. startRow: An integer representing the starting row of the move.
    3. startCol: An integer representing the starting column of the move.
    4. endRow: An integer representing the ending row of the move.
    5. endCol: An integer representing the ending column of the move.
    6. currentPlayer: A character representing the current player ('B' for Black, 'W' for White).
    7. display: A boolean value indicating whether to display the updated game state.

Return: 
    void

Algorithm:
    1. Update the game board by calling the updateBoard function of the Board object.
    2. If the display parameter is true:
        a. Print a message indicating that the game state is being updated.
        b. Display the updated game board by calling the displayBoard function of the Board object.
        c. Translate the move into A1 B2 notation using the reverseMoveTranslator function and print the translated move.

Reference: None
********************************************************************* */
void Computer::executeMove(Board& exBoard, int startRow, int startCol, int endRow, int endCol, char currentPlayer, bool display)
{
    exBoard.updateBoard(startRow, startCol, endRow, endCol, currentPlayer);
    if(display)
    {
        cout << "\n\nUpdating game state..." << endl;
        exBoard.displayBoard();
        string translatedMove = reverseMoveTranslator(exBoard, startRow, startCol, endRow, endCol);
        cout << "\nComputer Made Move: " << translatedMove << endl;
    }
    
}



/* *********************************************************************
Function Name: calculateDistanceToCenterScore
Purpose: To calculate the score based on the distance of a move to the center of the board.

Parameters:
    1. endRow: An integer representing the ending row of the move.
    2. endCol: An integer representing the ending column of the move.
    3. boardSize: An integer representing the size of the game board (number of rows/columns).

Return: 
    An integer representing the score based on the distance of the move to the center of the board.

Algorithm:
    1. Calculate the row and column indices of the center of the board by dividing the board size by 2.
    2. Calculate the Manhattan distance from the destination square to the center of the board.
    3. Calculate the distance score by subtracting the distance from the board size.
    4. Return the distance score.

Reference: None
********************************************************************* */
int Computer::calculateDistanceToCenterScore(int endRow, int endCol, int boardSize) {
    int centerRow = boardSize / 2;
    int centerCol = boardSize / 2;

    // Calculate Manhattan distance to the center of the destination square
    int distance = abs(endRow - centerRow) + abs(endCol - centerCol);

    // Assign a positive value to moves closer to the center (less distance is better)
    int distanceScore = boardSize - distance;

    return distanceScore;
}



// Function to give move recommendations to the human player during help mode
/* *********************************************************************
Function Name: provideMoveRecommendation
Purpose: To provide move recommendations to the human player during help mode.

Parameters:
    1. board: A reference to a Board object representing the current game board.
    2. currentPlayer: A character representing the current player's color ('B' for black, 'W' for white).

Return: 
    None

Algorithm:
    1. Clear the list of possible moves.
    2. Generate all possible legal moves for the player.
    3. Display the list of possible moves in A1 B2 notation.
    4. Recommend the best move based on the evaluation of possible moves.

Reference: None
********************************************************************* */
void Computer::provideMoveRecommendation(Board& board, char currentPlayer) {
    possibleMoves.clear();
    // Generate all possible legal moves for the player
    generatePossibleMoves(board, currentPlayer);

    // Display the list of possible moves
    cout << "Possible Moves:\n";
    for (int i = 0; i < possibleMoves.size(); i++) {
        int startRow = possibleMoves[i][0];
        int startCol = possibleMoves[i][1];
        int endRow = possibleMoves[i][2];
        int endCol = possibleMoves[i][3];
        string moveTranslated = reverseMoveTranslator(board, startRow, startCol, endRow, endCol);
        cout << "Move " << (i + 1) << ": " << moveTranslated << endl;
    }

    // Recommend the best move
    int bestMoveIndex = evaluateMoves(board, possibleMoves, currentPlayer);
    if (bestMoveIndex != -1) {
        int startRow = possibleMoves[bestMoveIndex][0];
        int startCol = possibleMoves[bestMoveIndex][1];
        int endRow = possibleMoves[bestMoveIndex][2];
        int endCol = possibleMoves[bestMoveIndex][3];
        string bestMoveTranslated = reverseMoveTranslator(board, startRow, startCol, endRow, endCol);
        cout << "\nRecommendation: Move " << (bestMoveIndex + 1) << " is the best move: " << bestMoveTranslated << endl;
    } else {
        cout << "\nNo valid moves found.\n";
    }
}



/* *********************************************************************
Function Name: reverseMoveTranslator
Purpose: To translate move indices to A1 B2 notation.

Parameters:
    1. board: A reference to a Board object representing the current game board.
    2. startRow: An integer representing the starting row index of the move.
    3. startCol: An integer representing the starting column index of the move.
    4. endRow: An integer representing the ending row index of the move.
    5. endCol: An integer representing the ending column index of the move.

Return: 
    A string representing the move in A1 B2 notation.

Algorithm:
    1. Convert row and column indices to letters for A1 B2 notation.
    2. Convert row indices to accurate numbers (in terms of board display).
    3. Construct the A1 B2 notation string and return it.

Reference: ChatGPT helped with ASCII char logic ('A' + col) and linking together string with ss
********************************************************************* */
string Computer::reverseMoveTranslator(Board& board, int startRow, int startCol, int endRow, int endCol)const {
    // Convert row and column indices to letters for A1 B2 notation
    char startColLetter = 'A' + startCol;
    char endColLetter = 'A' + endCol;

    // Convert row indices to numbers
    int startRowNumber = board.getBoardSize() - startRow;
    int endRowNumber = board.getBoardSize() - endRow;

    // Construct the A1 B2 notation string
    stringstream ss;
    ss << startColLetter << startRowNumber << " " << endColLetter << endRowNumber;
    return ss.str();
}





