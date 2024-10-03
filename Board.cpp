/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Board.cpp   (Board Class)                     *
     * Date:  2/20/24                                        *
*************************************************************/


#include "Board.h"


Board::Board() {
    // Initialize data members and set up the initial board state
    initializeBoard();
}

Board::~Board() {
    // Destructor 
}


//Function to set up the board in initial state
/* *********************************************************************
Function Name: initializeBoard
Purpose: Set up the board in the initial state.
   This function initializes the game board with pieces arranged in the starting configuration.

Parameters:
    None.

Return Value: 
    None.

Algorithm: 
    1. Iterate through each space of the board.
    2. If the current space is on the top or bottom rows, set it to 'B' (Black).
    3. If the current space is on the first or last columns, set it to 'W' (White).
    4. Otherwise, set the space to '.' (Empty).
    5. Check if the current space is one of the corner space, and if so, set it to '.' (Empty).

Reference: None
********************************************************************* */
void Board::initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (i == 0 || i == BOARD_SIZE - 1) {
                // Black pieces on top and bottom rows
                board[i][j] = 'B'; 
            } else if (j == 0 || j == BOARD_SIZE - 1) {
                // White pieces on first and last columns
                board[i][j] = 'W'; 
            }
            else {
                // Empty spaces in the middle
                board[i][j] = '.'; 
            }
            if((i == 0 && j == 0) || (i == 0 && j == BOARD_SIZE -1) || (i == BOARD_SIZE - 1 && j == BOARD_SIZE -1) || (i == BOARD_SIZE - 1 && j == 0))
            {
                // Empty spaces on the corners
                board[i][j] = '.'; 
            }
        }
    }
}


// Function to display the current state of the board with row and column labels
/* *********************************************************************
Function Name: displayBoard
Purpose: Display the current state of the board with row and column labels.

Parameters:
    None.

Return Value: 
    None.

Algorithm: 
    1. Print the letter labels for columns on the top row (A to H).
    2. Iterate through each row of the board, starting from the top row.
    3. Print the row number label on the left side of each row.
    4. Iterate through each space of the current row.
        a. Print the piece at the current space of the board.
        b. Separate each element with a space.
    5. Print the row number label again on the right side of each row.
    6. Repeat steps 2-5 for all rows.
    7. Print the letter labels for columns on the bottom row (A to H).

Reference: None
********************************************************************* */
void Board::displayBoard() const {
    // Letter labels on top
    cout << "  A B C D E F G H\n"; 
    for (int i = BOARD_SIZE - 1; i >= 0; --i) {
        //numbers on left side
        cout << (BOARD_SIZE - i) << " "; 
        for (int j = 0; j < BOARD_SIZE; ++j) {
            //actual pieces/board elements
            cout << board[i][j] << " "; 
        }
        //numbers on the right side
        cout << (BOARD_SIZE - i) << "\n"; 
    }
    // Letter labels on bottom
    cout << "  A B C D E F G H\n"; 
}


// Function to update the game state
/* *********************************************************************
Function Name: updateBoard
Purpose: Update the board state after a valid move.

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.
    currentPlayer (char): The character representing the current player.

Return Value: 
    None.

Algorithm: 
    1. Set the piece in the starting space to '.' (Empty).
    2. Set the piece in the destination space to the character representing the current player.

Reference: None
********************************************************************* */
void Board::updateBoard(int startRow, int startCol, int endRow, int endCol, char currentPlayer) {
    // Empty the starting position
    board[startRow][startCol] = '.'; 
    // Move the piece to the destination 
    board[endRow][endCol] = currentPlayer; 

}


// Function to get the piece/color at the specified row and column on the board
/* *********************************************************************
Function Name: getPiece
Purpose: Get the piece/color at the specified row and column on the board.

Parameters:
    row (int): The row index of the space.
    col (int): The column index of the space.

Return Value: 
    char: The character representing the piece/color at the specified position.
          Returns '.' if the position is outside the board bounds.

Algorithm: 
    1. Check if the given row and column values are within the board bounds.
    2. If the position is within bounds, return the piece at the specified position.
    3. If the position is outside the board bounds, return '.' (Empty).

Reference: None
********************************************************************* */
char Board::getPiece(int row, int col) const {
    // Check if the given row and column values are within the board bounds
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
        // Return the piece at the specified position
        return board[row][col]; 
    } else {
        // Return '.' if the position is outside the board
        return '.'; 
    }
}


// Function to get the count of pieces of the specified color on the board
/* *********************************************************************
Function Name: getPieceCount
Purpose: Get the count of pieces of the specified color on the board.

Parameters:
    color (char): The character representing the color of the pieces to count.

Return Value: 
    int: The count of pieces of the specified color on the board.

Algorithm: 
    1. Initialize a variable 'count' to 0 to store the number of pieces.
    2. Iterate through each space of the board.
    3. If the piece at the current space is of the specified color, increment the count.
    4. After processing all spaces, return the count.

Reference: None
********************************************************************* */
int Board::getPieceCount(char color) const {
    // Initialize count variable to store the number of pieces
    int count = 0; 

    // Iterate through the board and count pieces of the specified color
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == color) {
                // Increase count if the current position contains a piece of the given color
                count++; 
            }
        }
    }

    // Return the total count of pieces of the specified color
    return count; 
}


//Returns BOARD_SIZE
/* *********************************************************************
Function Name: getBoardSize
Purpose: Return the size of the board.

Parameters:
    None.

Return Value: 
    int: The size of the board.

Algorithm: 
    1. Return the constant value BOARD_SIZE.

Reference: None
********************************************************************* */
int Board::getBoardSize() const 
{
    return BOARD_SIZE;
}





/* *********************************************************************
Function Name: saveToFile
Purpose: Save the current state of the board to a file.

Parameters:
    filename (const string&): A constant reference to a string representing the name of the file to save the board state to.

Return Value: 
    bool: true if the board state is successfully saved to the file, false otherwise.

Algorithm: 
    1. Attempt to open the file specified by the filename for writing.
    2. If the file cannot be opened, print an error message to the standard error stream and return false.
    3. Write the board state to the file, with each space/element separated by a space character.
    4. Close the file.
    5. Print a success message to the standard output stream showing that the board state has been saved to the file.
    6. Return true to indicate success.

Reference: None
********************************************************************* */
bool Board::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return false;
    }

    // Write the board configuration to the file
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            outFile << board[i][j] << " ";
        }
        outFile << endl;
    }

    outFile.close();
    cout << "Board state saved to file: " << filename << endl;
    return true;
}


/* *********************************************************************
Function Name: loadFromFile
Purpose: Load the board state from a file.

Parameters:
    filename (const string&): A constant reference to a string representing the name of the file from which to load the board state.

Return Value: 
    bool: true if the board state is successfully loaded from the file, false otherwise.

Algorithm: 
    1. Attempt to open the file specified by the filename for reading.
    2. If the file cannot be opened, print an error message to the error stream and return false.
    3. Read the board state from the file, assuming each space is separated by a space character.
    4. If any error occurs during reading (or board is invalid), print an error message to the standard error stream and return false.
    5. Close the file.
    6. Print a success message to the standard output stream indicating that the board state has been loaded from the file.
    7. Return true to indicate success.

Reference: None
********************************************************************* */
bool Board::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
        return false;
    }

    // Read the board configuration from the file
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (!(inFile >> board[i][j])) {
                cerr << "Error: Failed to read board configuration from file: " << filename << endl;
                return false;
            }
            if (board[i][j] != 'W' && board[i][j] != 'B' && board[i][j] != '.')
            {
                cerr << "Error: Invalid board characters in file (must be 'W' 'B' and '.' only)" << endl;
                return false;
            }
        }
    }

    inFile.close();
    cout << "Board state loaded from file: " << filename << endl;
    return true;
}




//********* Move Validation Functions ***************


//Function to definitively determine if a move is valid or not
/* *********************************************************************
Function Name: validateMove
Purpose: Determine if a move is valid or not based on game rules.

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.
    currentPlayer (char): The character representing the current player.

Return Value: 
    bool: true if the move is valid, false otherwise.

Algorithm: 
    1. Check if the starting and destination spaces are within the board bounds.
    2. Check if the move is in a valid direction (horizontal, vertical, or diagonal).
    3. Check if the starting space contains a piece belonging to the current player.
    4. Check if the destination space is not occupied by a piece of the current player's color.
    5. Check if the lane from the starting space to the destination space is free of opposing pieces.
    6. Check if the move is of the correct distance according to the piece's movement rules.
    7. If any of the above conditions fail, print an error message indicating the reason for invalidity and return false.
    8. If all conditions pass, return true to indicate a valid move.

Reference: None
********************************************************************* */
bool Board::validateMove(int startRow, int startCol, int endRow, int endCol, char currentPlayer) const {
    // Check if a player's move is valid based on game rules
    if (!isWithinBoard(startRow, startCol) || !isWithinBoard(endRow, endCol)) {
        cout << "\nMove not within board...\n";
        return false; // Move is outside the board
    }
    

    // Check if the move follows the correct direction and distance based on the piece's movement rules
    if (!isHorizontalMove(startRow, startCol, endRow, endCol) &&
        !isVerticalMove(startRow, startCol, endRow, endCol) &&
        !isDiagonalMove(startRow, startCol, endRow, endCol)) {
        cout << "\nMove not vertical, horizontal, or vertical...\n";
        return false;
    }


    // Check if the starting square contains a piece belonging to the current player
    if (getPiece(startRow, startCol) != currentPlayer) {
        cout << "\nMove not with correct player color...\n";
        return false;
    }

    //Check to see if the destination square is our own piece
    if (!isNotOccupiedByOwnColor(startRow, startCol, endRow, endCol, currentPlayer))
    {
        cout << "\nMove attempts to capture friendly piece...\n";
        return false;
    }

    // Check to see if the lane is obstructed by opposing pieces
    if(!isFreeLane(startRow, startCol, endRow, endCol, currentPlayer))
    {
        cout << "\nMove not in free lane...\n";
        return false;
    }


    // Check to see if the move is the correct distance (ex: 2 pieces in col, move two spaces)
   if(!isCorrectMoveDistance(startRow, startCol, endRow, endCol))
    {
        cout << "\nMove not correct distance...\n";
        return false;
    }

    return true;
}


//Checks if move is within board limits
/* *********************************************************************
Function Name: isWithinBoard
Purpose: Check if a given space is within the board limits.

Parameters:
    row (int): The row index of the space.
    col (int): The column index of the space.

Return Value: 
    bool: true if the space is within the board limits, false otherwise.

Algorithm: 
    1. Check if the row index is within the range [0, BOARD_SIZE-1].
    2. Check if the column index is within the range [0, BOARD_SIZE-1].
    3. Return true if both conditions are satisfied, indicating that the space is within the board limits.
    4. Return false otherwise.

Reference: None
********************************************************************* */
bool Board::isWithinBoard(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}


//Checks if given move is a horizontal move
/* *********************************************************************
Function Name: isHorizontalMove
Purpose: Check if a given move is a horizontal move.

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.

Return Value: 
    bool: true if the move is horizontal, false otherwise.

Algorithm: 
    1. Check if the row index of the starting space is equal to the row index of the destination space.
    2. Return true if the condition is satisfied, indicating that the move is horizontal.
    3. Return false otherwise.

Reference: None
********************************************************************* */
bool Board::isHorizontalMove(int startRow, int startCol, int endRow, int endCol) const {
    return startRow == endRow;
}


//Checks if given move is a vertical move
/* *********************************************************************
Function Name: isVerticalMove
Purpose: Check if a given move is a vertical move.

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.

Return Value: 
    bool: true if the move is vertical, false otherwise.

Algorithm: 
    1. Check if the column index of the starting space is equal to the column index of the destination space.
    2. Return true if the condition is satisfied, indicating that the move is vertical.
    3. Return false otherwise.

Reference: None
********************************************************************* */
bool Board::isVerticalMove(int startRow, int startCol, int endRow, int endCol) const {
    return startCol == endCol;
}


//Checks if given move is a diagonal move
/* *********************************************************************
Function Name: isDiagonalMove
Purpose: Check if a given move is a diagonal move.

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.

Return Value: 
    bool: true if the move is diagonal, false otherwise.

Algorithm: 
    1. Calculate the absolute difference between the row indices of the starting and destination spaces.
    2. Calculate the absolute difference between the column indices of the starting and destination spaces.
    3. Check if the absolute differences in row and column indices are equal.
    4. Return true if the condition is satisfied, indicating that the move is diagonal.
    5. Return false otherwise.

Reference: None
********************************************************************* */
bool Board::isDiagonalMove(int startRow, int startCol, int endRow, int endCol) const {
    return abs(startRow - endRow) == abs(startCol - endCol);
}


//Checks if the destination square is not occupied by own color (capturing own piece)
/* *********************************************************************
Function Name: isNotOccupiedByOwnColor
Purpose: Check if the destination square is not occupied by the current player's own color (capturing own piece).

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.
    currentPlayer (char): The character representing the current player.

Return Value: 
    bool: true if the destination square is not occupied by the current player's own color, false otherwise.

Algorithm: 
    1. Check if the piece at the destination space is the same as the current player's color.
    2. Return false if the condition is satisfied, indicating that capturing own piece is invalid.
    3. Return true otherwise, indicating that the move is valid.

Reference: None
********************************************************************* */
bool Board::isNotOccupiedByOwnColor(int startRow, int startCol, int endRow, int endCol, char currentPlayer) const
{
    if (getPiece(endRow, endCol) == currentPlayer) {
        return false; // Move is invalid if attempting to capture own piece
    }
    return true;
}


//Checks if given move is in a free lane (no jumping opposing pieces)
/* *********************************************************************
Function Name: isFreeLane
Purpose: Check if a given move is in a free lane (no jumping opposing pieces).

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.
    currentPlayer (char): The character representing the current player.

Return Value: 
    bool: true if the move is in a free lane, false otherwise.

Algorithm: 
    1. Determine the direction of movement for rows and columns (check change in row and column from start to end square).
    2. Initialize the current row and column to the next space in the direction of movement.
    3. Iterate over the spaces between the starting and ending spaces.
    4. Check if each space contains an opponent's piece.
    5. If any opponent's piece is found in the path, return false to indicate that the move is invalid.
    6. If no obstacles are found, return true to indicate that the move is valid.

Reference: None
********************************************************************* */
bool Board::isFreeLane(int startRow, int startCol, int endRow, int endCol, char currentPlayer) const {
    // Determine the direction of movement for rows
    int deltaRow;
    if (endRow > startRow) {
        deltaRow = 1;
    } else if (endRow < startRow) {
        deltaRow = -1;
    } else {
        deltaRow = 0;
    }

    // Determine the direction of movement for columns
    int deltaCol;
    if (endCol > startCol) {
        deltaCol = 1;
    } else if (endCol < startCol) {
        deltaCol = -1;
    } else {
        deltaCol = 0;
    }

    // Initialize the current row to the row next to the starting row
    int currentRow = startRow + deltaRow;
    // Initialize the current column to the column next to the starting column
    int currentCol = startCol + deltaCol;


    // Iterate over the squares between the starting and ending squares
    while (currentRow != endRow || currentCol != endCol) {
        // Check if the current square is occupied by the opponent's piece
        if (getPiece(currentRow, currentCol) != '.' && getPiece(currentRow, currentCol) != currentPlayer) {
            return false; // Move is invalid if there is an obstacle (opponent's piece) in the path
        }
        // Move to the next square
        currentRow += deltaRow;
        currentCol += deltaCol;
    }

    // If no obstacles are found, the move is valid
    return true;
}


//Checks if given move is equal in distance to the number of pieces in its given lane
/* *********************************************************************
Function Name: isCorrectMoveDistance
Purpose: Check if a given move is equal in distance to the number of pieces in its given lane.

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.

Return Value: 
    bool: true if the move is correct in distance, false otherwise.

Algorithm: 
    1. Determine the direction of movement by calculating the differences in row and column indices.
    2. Initialize variables to count the number of pieces encountered and the distance moved.
    3. If the movement is horizontal:
        a. Count the number of non-empty squares in the row.
        b. Calculate the absolute difference in column indices as the distance moved.
    4. If the movement is vertical:
        a. Count the number of non-empty squares in the column.
        b. Calculate the absolute difference in row indices as the distance moved.
    5. If the movement is diagonal:
        a. For each diagonal direction, count the number of non-empty squares.
        b. Calculate the sum of absolute differences in row and column indices divided by 2 as the distance moved.
    6. Compare the number of pieces encountered with the distance moved.
    7. Return true if they are equal, indicating that the move is correct in distance.
    8. Return false otherwise.

Reference: None
********************************************************************* */
bool Board::isCorrectMoveDistance(int startRow, int startCol, int endRow, int endCol) const {
    // Calculate the differences in row and column indices to determine the direction of movement
    int deltaRow = endRow - startRow;
    int deltaCol = endCol - startCol;

    // Initialize a variable to count the number of pieces encountered along the movement path
    int pieceCount = 0;

    //Intialize a variable to hold the total traveled distance of the move
    int distanceMoved = 0;

    // Check if the movement is horizontal
    if (isHorizontalMove(startRow, startCol, endRow, endCol)) {
        // Count the number of non-empty squares in the row
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (getPiece(startRow, col) != '.') {
                pieceCount++;
            }
        }
        // Calculate the distance moved 
        distanceMoved = abs(deltaCol);
    }
    // Check if the movement is vertical
    else if (isVerticalMove(startRow, startCol, endRow, endCol)) {
        // Count the number of non-empty squares in the column
        for (int row = 0; row < BOARD_SIZE; row++) {
            if (getPiece(row, startCol) != '.') {
                pieceCount++;
            }
        }
        // Calculate the distance moved 
        distanceMoved = abs(deltaRow);
    }
    // Check if the movement is diagonal
    else if (isDiagonalMove(startRow, startCol, endRow, endCol)) {

        if (startCol < endCol) { //Condition for right diagonal
            // Count the number of non-empty squares in the diagonal
            int row = startRow;
            int col = startCol;
            while (row >= 0 && col >= 0) {
                if (getPiece(row, col) != '.') {
                    pieceCount++;
                }
                row--;
                col--;
            }

            row = startRow + 1;
            col = startCol + 1;

            while (row <= BOARD_SIZE && col <= BOARD_SIZE) {
                if (getPiece(row, col) != '.') {
                    pieceCount++;
                }
                row++;
                col++;
            }
        } else { // Condition for left diagonal
            // Count the number of non-empty squares in the diagonal
            int row = startRow;
            int col = startCol;
            while (row >= 0 && col <= BOARD_SIZE) {
                if (getPiece(row, col) != '.') {
                    pieceCount++;
                }
                row--;
                col++;
            }

            row = startRow + 1;
            col = startCol - 1;

            while (row <= BOARD_SIZE && col >= 0) {
                if (getPiece(row, col) != '.') {
                    pieceCount++;
                }
                row++;
                col--;
            }
        }
        // Calculate the distance moved (sum of absolute differences in row and column indices, divided by 2)
        distanceMoved = (abs(deltaRow) + abs(deltaCol)) / 2;
    }

    

    // Compare the number of pieces encountered with the distance moved
    return pieceCount == distanceMoved;
}



/* *********************************************************************
Function Name: cpuMoveCheck
Purpose: Check if a move is valid for the CPU player based on game rules.

Parameters:
    startRow (int): The row index of the starting space of the move.
    startCol (int): The column index of the starting space of the move.
    endRow (int): The row index of the destination space of the move.
    endCol (int): The column index of the destination space of the move.
    currentPlayer (char): The character representing the current player.

Return Value: 
    bool: true if the move is valid for the CPU player, false otherwise.

Algorithm: 
    1. Check if the starting and destination spaces are within the board bounds.
    2. Check if the move is in a valid direction (horizontal, vertical, or diagonal).
    3. Check if the starting space contains a piece belonging to the current player.
    4. Check if the destination space is not occupied by a piece of the current player's color.
    5. Check if the lane from the starting space to the destination space is free of opposing pieces.
    6. Check if the move is of the correct distance according to the piece's movement rules.
    7. Return true if all conditions pass, indicating a valid move for the CPU player.
    8. Return false otherwise.

Reference: None
********************************************************************* */
bool Board::cpuMoveCheck(int startRow, int startCol, int endRow, int endCol, char currentPlayer)
{

    if (!isWithinBoard(startRow, startCol) || !isWithinBoard(endRow, endCol)) {
        return false; // Move is outside the board
    }
    

    // Check if the move follows the correct direction and distance based on the piece's movement rules
    if (!isHorizontalMove(startRow, startCol, endRow, endCol) &&
        !isVerticalMove(startRow, startCol, endRow, endCol) &&
        !isDiagonalMove(startRow, startCol, endRow, endCol)) {
        return false;
    }


    // Check if the starting square contains a piece belonging to the current player
    if (getPiece(startRow, startCol) != currentPlayer) {
        return false;
    }


    //Check to see if the destination square is our own piece
    if (!isNotOccupiedByOwnColor(startRow, startCol, endRow, endCol, currentPlayer))
    {
        return false;
    }

    // Check to see if the lane is obstructed by opposing pieces
    if(!isFreeLane(startRow, startCol, endRow, endCol, currentPlayer))
    {
        return false;
    }


    // Check to see if the move is the correct distance (ex: 2 pieces in col, move two spaces)
   if(!isCorrectMoveDistance(startRow, startCol, endRow, endCol))
    {
        return false;
    }

    return true;
}


