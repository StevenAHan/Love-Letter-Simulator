#ifndef LOVELETTERSIM_GAME_H
#define LOVELETTERSIM_GAME_H
#include <iostream>
#include <string>
#include <vector>
#include "Deck.h"

class Player;

class Game {
public:
    Game();

    void addPlayer(Player& player);

    void playGame();

    Player* findPlayer(const std::string& name);

    Card* drawCard();

    void discard(Card* card);

    void weakDiscard(Card* card);

    void endGame();

private:
    std::vector<Player*> players;
    Deck deck;
};

#endif //LOVELETTERSIM_GAME_H
