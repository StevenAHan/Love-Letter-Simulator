#ifndef LOVELETTERSIM_PLAYER_H
#define LOVELETTERSIM_PLAYER_H
#include <iostream>
#include <string>
#include<vector>

class Card;
class Game;

class Player {
public:
    Player(const std::string& name);

    ~Player();

//    Player(const Player& rhs);
//
//    Player& operator=(const Player& rhs);

    void playCurrCard();

    void playDrawnCard();

    void loseCard();

    const std::string& getName() const;

    int getCurrCardNum() const;

    bool isAlive() const;

    void killPlayer();

    void setGame(Game* theGame);

    void drawCard();

    void showHand() const;

    void getCardDesc() const;

    bool isImmune() const;

    void setImmunity(bool im);

    void swap(Player* other);

    void showCurrCard() const;

    bool hasCountessConditions() const;

    Card* getCurrCard() const;

    Card* getDrawnCard() const;

    void deleteInv();

    void reset();

private:
    std::string name;
    bool alive;
    Card* currCard;
    Card* drawnCard;
    Game* currGame;
    bool immunity;
};


#endif //LOVELETTERSIM_PLAYER_H
