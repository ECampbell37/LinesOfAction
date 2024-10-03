/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Round.cpp   (Round  Class)                    *
     * Date:  2/20/24                                        *
*************************************************************/

#include "Round.h"


Round::Round() : gameOver(false) {}

Round::~Round() {}



/* *********************************************************************
Function Name: isGameOver
Purpose: Check if the round is over.

Return: 
    bool: true if the round is over, false otherwise.

Algorithm: 
    1. Return the gameOver attribute of the round.

Reference: None
********************************************************************* */
bool Round::isGameOver() const {
    return gameOver;
}


/* *********************************************************************
Function Name: setGameOver
Purpose: Set the game over state of the round.

Parameters:
    state (bool): The game over state to set.

Return: 
    void

Algorithm: 
    1. Set the gameOver attribute of the round to the specified state.

Reference: None
********************************************************************* */
void Round::setGameOver(bool state) {
    gameOver = state;
}