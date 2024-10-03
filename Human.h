/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Human.h   (Human Class)                       *
     * Date:  2/20/24                                        *
*************************************************************/


#ifndef HUMAN_H
#define HUMAN_H

#include "stdafx.h"
#include "Player.h"
#include "Board.h"
#include "Round.h"

class Human : public Player {
public:
    // Constructor
    Human(char color);

    // Destructor
    ~Human();

    // Function to make a move on the game board
    void executeMove(Board& board);

    // Inherited playerAction function
    void playerAction(Board& board, Round& round) override;

    
};

#endif // HUMAN_H
