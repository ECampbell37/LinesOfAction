/************************************************************
     * Name:  Elijah Campbell-Ihim                           *
     * Project:  Lines of Action                             *
     * Class:  Tournament.h   (Tournament Class)             *
     * Date:  2/20/24                                        *
*************************************************************/


#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Round.h"

class Tournament {
private:
    Player& player1; // Reference to Human Player
    Player& player2; // Reference to Computer Player
    

public:
    Tournament(Player& player1, Player& player2); // Constructor
    ~Tournament();
    void startTournament(Board& gameBoard); // Method to start the tournament
    void playRound(Board& gameBoard); // Method to play a single round
    void announceWinner(); // Method to announce the tournament winner
};

#endif

