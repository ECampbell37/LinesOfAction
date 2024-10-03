/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Player.h   (Player Class)                     *
     * Date:  2/20/24                                        *
*************************************************************/


#ifndef PLAYER_H //Used to avoid repeat declaration
#define PLAYER_H

#include "stdafx.h"
#include "Board.h"
#include "Round.h"

class Player {
private:
    char color; // Player's color (w for white, b for black)
    int wins = 0; // Number of wins player has
    


public:
    static const int MOVE_SIZE = 4;  // for size of move array
    int move[MOVE_SIZE]; //Array for holding current user move values


    // Constructor
    Player(char color);

    // Destructor
    virtual ~Player();

    // Get
    char getColor() const;

    int getWins() const;


    //Set
    void setWins(int val);
    void increaseWin();


    // Move execution function (to be overridden by subclasses), partially used Chat GPT for override
    virtual void playerAction(Board& board, Round& round) = 0;



    //Function for translating moves string -> numerical (used CHAT GPT for ASCII math)
    void inputTranslator(const string& start, const string& end, int* translatedValues);


    int calcConnectedPieces(const Board& board) const;

    //Function to determine winner
    bool isWinner(const Board& board) const;


};

#endif // PLAYER_H
