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

    size_t playGame(size_t firstPlayer);

    Player* findPlayer(const std::string& name);

    Card* drawCard();

    void discard(Card* card);

    void weakDiscard(Card* card);

    void endGame();

    void playFullGame();

    void resetPlayers();

private:
    std::vector<Player*> players;
    std::vector<int> wins;
    Deck deck;
};

#endif //LOVELETTERSIM_GAME_H