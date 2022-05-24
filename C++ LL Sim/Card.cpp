#include "Card.h"
#include "Player.h"
#include "Game.h"
using namespace std;

// Card Class Code
Card::Card(const string& name, const string& desc, int num) :
        cardName(name), cardDesc(desc), cardNum(num), player(nullptr) {}

const string& Card::getName() const
{
    return cardName;
}

const string& Card::getDesc() const
{
    return cardDesc;
}

int Card::getNum() const
{
    return cardNum;
}

Player* Card::targetPlayer(Game* currGame) const
{
    cout <<  "What player do you want to target? (Input Name)" << endl;
    string name;
    cin >> name;
    Player* target = currGame->findPlayer(name);
    while(!(target && target->isAlive() && !target->isImmune()))
    {
        if(!target)
            cout << "Player doesn't exist! Try again." << endl;
        else if (!target->isAlive())
            cout << "Player is already dead! Try again." << endl;
        else
            cout << "Player is immune due to Handmaiden. Try again." << endl;

        cout <<  "What player do you want to target? (Input Name)" << endl;
        string name;
        cin >> name;
        target = currGame->findPlayer(name);
    }
    return target;
}

void Card::getFullDesc() const
{
    cout << "Name: " << cardName << " (" << cardNum << ")\nDescription: " << cardDesc << endl;
}

void Card::setPlayer(Player* pr)
{
    player = pr;
}

Player* Card::getPlayer() const
{
    return player;
}

// Guard Class Code
Guard::Guard() : Card("Guard", "Name a number other than 1 and choose another player. "
                               "\nIf they have that number in their hand, "
                               "they are knocked out of the round.", 1) {}


void Guard::discard(Game* currGame)
{
    // Find Player somehow
    Player* target = targetPlayer(currGame);
    // Choose number
    cout << "What number are you guessing? (Must be between 2 - 8)" << endl;
    int num = 0;
    while(num <= 1 || num >= 9)
    {
        cin >> num;
        if(num <= 1 || num >= 9)
            cout << "Following instructions must not be your strong suit. Try again." << endl;
    }
    bool killed = attemptKill(target, num);
    if(killed)
        cout << "Nice! You killed the other player!" << endl;
    else
        cout << "You guessed incorrectly, and the player is still alive. :(" << endl;
}

bool Guard::attemptKill(Player* target, int num)
{
    if(target->getCurrCardNum() == num)
    {
        target->killPlayer();
        return true;
    }
    return false;
}

// Priest Class Code
Priest::Priest() : Card("Priest", "Look at another player's hand.", 2) {}

void Priest::discard(Game* currGame)
{
    Player* target = targetPlayer(currGame);
    target->showCurrCard();
}

// Baron Class Code
Baron::Baron() : Card("Baron", "You and another player secretly compare hands. "
                               "\nThe player with the lower value is out of the round.", 3) {}

void Baron::discard(Game* currGame)
{
    Player* target = targetPlayer(currGame);
    target->showCurrCard();
    Card* currPlayerCard = getPlayer()->getCurrCard();
    if(currPlayerCard->getName() == "Baron")
    {
        currPlayerCard = getPlayer()->getDrawnCard();
    }
    if(target->getCurrCardNum() < currPlayerCard->getNum())
    {
        target->killPlayer();
        cout << "Nice! You killed " << target->getName() << "!" << endl;
    }
    else if(target->getCurrCardNum() > currPlayerCard->getNum())
    {
        getPlayer()->killPlayer();
        cout << "Whoops! You died!\n";
    }
    else
    {
        cout << "Nothing happened cause you tied :/" << endl;
    }
}

// Handmaid Class Code
Handmaid::Handmaid() : Card("Handmaid", "Until your next turn, "
                                        "ignore all effects from the other players' cards.", 4) {}
void Handmaid::discard(Game* currGame)
{
    Player* player = getPlayer();
    player->setImmunity(true);
}

// Prince Class Code
Prince::Prince() : Card("Prince", "Choose any player (including yourself) "
                                  "to discard his or her hand and draw a new card.", 5) {}

void Prince::discard(Game* currGame)
{
    Player* target = targetPlayer(currGame);
    target->loseCard();
}

// King Class Code
King::King() : Card("King", "Trade hands with another player of your choice.", 6) {}

void King::discard(Game* currGame) // NOT WORKING
{
    Player* target = targetPlayer(currGame);
    getPlayer()->swap(target);
}

// Countess Class Code
Countess::Countess() : Card("Countess", "If you have this card and the King or Prince in your hand, "
                                        "you must discard this card.", 7) {}

void Countess::discard(Game* currGame)
{
    // Does nothing
}

// Princess Class Code
Princess::Princess() : Card("Princess", "If you discard this card, you are out of the round.", 8) {}

void Princess::discard(Game* currGame)
{
    cout << "You discarded the Princess! Die!" << endl;
    getPlayer()->killPlayer();
}
