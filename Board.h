/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Board.h   (Board Class)                       *
     * Date:  2/20/24                                        *
*************************************************************/


#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"

class Board {
private:
    static const int BOARD_SIZE = 8; // constant to represent board size 
    char board[BOARD_SIZE][BOARD_SIZE];  // Using char 2D array to represent pieces and positions ('W', 'B', or '.')

public:
    // Constructor
    Board();

    // Destructor
    ~Board();

    // Public functions
    void initializeBoard();
    void displayBoard() const;
    bool validateMove(int startRow, int startCol, int endRow, int endCol, char currentPlayer) const;
    bool cpuMoveCheck(int startRow, int startCol, int endRow, int endCol, char currentPlayer);
    void updateBoard(int startRow, int startCol, int endRow, int endCol, char currentPlayer);
    
    //Get Functions
    char getPiece(int row, int col) const;
    int getPieceCount(char color) const;
    int getBoardSize() const;
    

    //Serialization Functions
    bool saveToFile(const string& filename) const;
    bool loadFromFile(const string& filename);
    


private:
    //Private helper functions for validation
    bool isWithinBoard(int row, int col) const;
    bool isHorizontalMove(int startRow, int startCol, int endRow, int endCol) const;
    bool isVerticalMove(int startRow, int startCol, int endRow, int endCol) const;
    bool isDiagonalMove(int startRow, int startCol, int endRow, int endCol) const;
    bool isNotOccupiedByOwnColor(int startRow, int startCol, int endRow, int endCol, char currentPlayer) const;
    bool isFreeLane(int startRow, int startCol, int endRow, int endCol, char currentPlayer)const;
    bool isCorrectMoveDistance(int startRow, int startCol, int endRow, int endCol) const;
};

#endif // BOARD_H
