/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Computer.h   (Computer Class)                 *
     * Date:  2/20/24                                        *
*************************************************************/


#ifndef COMPUTER_H
#define COMPUTER_H

#include "Board.h"
#include "Player.h"

class Computer : public Player{
private:
    // Vector to store all possible moves
    vector<vector<int>> possibleMoves;


public:
    // Constructor
    Computer(char color);

    // Destructor
    ~Computer();

    // Function to generate all possible legal moves for the computer player
    void generatePossibleMoves(Board& board, char currentPlayer);

    //Function to score moves based on connectiveness before and after
    int evaluateMoves(const Board& board, const vector<vector<int>>& possibleMoves, char currentPlayer);

    // Function to choose the best move based on some criteria
    void selectBestMove(Board& board, char currentPlayer);

    //Function to execute a given move on a given board
    void executeMove(Board& exBoard, int startRow, int startCol, int endRow, int endCol, char currentPlayer, bool display);

    //Inherited function from Player class
    void playerAction(Board& board, Round& round) override;

    //Function to calculate move score from distance from center
    int calculateDistanceToCenterScore(int endRow, int endCol, int boardSize);

    // Function to give move recommendations to the human player during help mode
    void provideMoveRecommendation(Board& board, char currentPlayer);

    //Function to translate move in numeric format to "A1 B2" format
    string reverseMoveTranslator(Board& board, int startRow, int startCol, int endRow, int endCol)const;

    
};

#endif // COMPUTER_H
