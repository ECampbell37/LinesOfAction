/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Round.h   (Round Class)                       *
     * Date:  2/20/24                                        *
*************************************************************/


#ifndef ROUND_H
#define ROUND_H

class Round {
private:
    bool gameOver; // Variable to manage game state

public:
    // Constructor
    Round();

    // Destructor
    ~Round();

    // Method to check if the game is over
    bool isGameOver() const;

    // Method to set the game over state
    void setGameOver(bool state);
};


#endif // ROUND_H



