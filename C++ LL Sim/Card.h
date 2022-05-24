#ifndef LOVELETTERSIM_CARD_H
#define LOVELETTERSIM_CARD_H
#include <iostream>
#include <string>
#include<vector>

class Game;
class Player;

class Card {
public:
    Card(const std::string& name, const std::string& desc, int num);

    const std::string& getName() const;

    const std::string& getDesc() const;

    virtual void discard(Game* currGame) = 0;

    int getNum() const;

    Player* targetPlayer(Game* currGame) const;

    void getFullDesc() const;

    void setPlayer(Player* pr);

    Player* getPlayer() const;

private:
    std::string cardName;
    std::string cardDesc;
    int cardNum;
    Player* player;
};

class Guard : public Card {
public:
    Guard();

    // Guess a person and a number. Kill if everything works
    void discard(Game* currGame) override;

    bool attemptKill(Player* target, int num);
};

class Priest : public Card {
public:
    Priest();

    // Look at someone else's hand
    void discard(Game* currGame) override;
};

class Baron : public Card {
public:
    Baron();

    // Fight!
    void discard(Game* currGame) override;
};

class Handmaid : public Card {
public:
    Handmaid();

    // Can't be targetted until it is your turn again
    void discard(Game* currGame) override;
};

class Prince : public Card {
public:
    Prince();

    // Discard and draw
    void discard(Game* currGame) override;
};

class King : public Card {
public:
    King();

    // Trade hands
    void discard(Game* currGame) override;
};

class Countess : public Card {
public:
    Countess();

    // Do nothing
    void discard(Game* currGame) override;
};

class Princess : public Card {
public:
    Princess();

    // Lose the game
    void discard(Game* currGame) override;
};


#endif //LOVELETTERSIM_CARD_H