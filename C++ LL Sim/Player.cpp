#include "Player.h"
#include "Card.h"
#include "Game.h"
using namespace std;

// Player Class Code
Player::Player(const string& name) :
    name(name), currCard(nullptr), drawnCard(nullptr), alive(true), immunity(false) {}

Player::~Player()
{
    deleteInv();
}

//Player::Player(const Player& rhs) : name(rhs.name)
//{
//    if(rhs.currCard)
//        currCard = new Card(rhs.currCard);
//}

void Player::playCurrCard()
{
    cout << name << " plays " << currCard->getName() << endl;
    currGame->discard(currCard);
    currCard->setPlayer(nullptr);
    currCard = drawnCard;
    drawnCard = nullptr;
}

void Player::playDrawnCard()
{
    cout << name << " plays " << drawnCard->getName() << endl;
    currGame->discard(drawnCard);
    drawnCard->setPlayer(nullptr);
    drawnCard = nullptr;
}

void Player::loseCard()
{
    if(currCard == nullptr)
    {
        cout << name << " discarded " << drawnCard->getName() << endl;
        drawnCard->setPlayer(nullptr);
        currGame->weakDiscard(drawnCard);
        drawnCard = nullptr;
    }
    else
    {
        cout << name << " discarded " << currCard->getName() << endl;
        if(currCard->getName() == "Princess")
        {
            cout << "That's the Princess! Guess you die!\n";
            killPlayer();
        }
        currCard->setPlayer(nullptr);
        currGame->weakDiscard(currCard);
        currCard = nullptr;
        if(alive)
        {
            drawCard();
        }
    }
}

const string& Player::getName() const
{
    return name;
}

int Player::getCurrCardNum() const
{
    return currCard->getNum();
}

bool Player::isAlive() const
{
    return alive;
}

void Player::killPlayer()
{
    alive = false;
}

void Player::setGame(Game* theGame)
{
    currGame = theGame;
}

void Player::drawCard()
{
    if(!currCard)
    {
        currCard = currGame->drawCard();
        currCard->setPlayer(this);
    }
    else if(!drawnCard)
    {
        drawnCard = currGame->drawCard();
        drawnCard->setPlayer(this);
    }
    else
        cerr << "Full hand!";
}

void Player::showHand() const
{
    cout << "Card 1: " << currCard->getName() << endl;
    cout << "Card 2: " << drawnCard->getName() << endl;
}

void Player::getCardDesc() const
{
    cout << "Card 1: \n";
    currCard->getFullDesc();
    cout << "\nCard 2: \n";
    drawnCard->getFullDesc();
}

bool Player::isImmune() const
{
    return immunity;
}

void Player::setImmunity(bool im)
{
    immunity = im;
}

// TODO
void Player::swap(Player* other)
{
    Card* otherCurr = other->currCard;
    Card* yourCard = currCard;
    if(yourCard->getName() == "King")
    {
        yourCard = drawnCard;
    }
    otherCurr->setPlayer(this);
    yourCard->setPlayer(other);
    other->currCard = yourCard;
    if(currCard->getName() == "King")
    {
        drawnCard = otherCurr;
    }
    else
    {
        currCard = otherCurr;
    }
}

void Player::showCurrCard() const
{
    cout << name << " is currently holding a " <<currCard->getName() << endl;
}

bool Player::hasCountessConditions() const {
    if (currCard->getName() == "Countess")
        if (drawnCard->getNum() >= 5 && drawnCard->getNum() < 8)
            return true;
    else if (drawnCard->getNum() == 7)
        if (currCard->getNum() >= 5 && currCard->getNum() < 8)
            return true;
    return false;
}

Card* Player::getCurrCard() const
{
    return currCard;
}

Card* Player::getDrawnCard() const
{
    return drawnCard;
}

void Player::deleteInv()
{
    if(currCard)
        delete currCard;
    if(drawnCard)
        delete drawnCard;
}
