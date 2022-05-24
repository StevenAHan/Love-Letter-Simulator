/*
 Steven Han

 LoveLetterSimulator

 This program will simulate a game of the card game Love Letter.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Card.h"

using namespace std;

// TODO
/*class ExpansionCard : public Card {

 };*/


int main() {
    // 1. Create a game class
    Game game;

    // 2. Populate the players
    Player steve("Steven");
    Player kev("Kevin");
    Player jon("Jonathan");
    game.addPlayer(steve);
    game.addPlayer(kev);
    game.addPlayer(jon);

    // 3. Play the game
    game.playFullGame();

}
