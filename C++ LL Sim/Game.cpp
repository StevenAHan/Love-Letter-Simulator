#include "Game.h"
#include "Player.h"
#include "Card.h"
using namespace std;


// Game Class Code
Game::Game() : deck(0) {}

void Game::addPlayer(Player& player) {
    for (size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->getName() == player.getName())
        {
            cerr << "Name already in this game. Player not added." << endl;
            return;
        }
    }
    players.push_back(&player);
    player.setGame(this);
}

size_t Game::playGame(size_t firstPlayer)
{
    // Create a deck
    deck = Deck(players.size());
    deck.createDeck();

    // Shuffle the deck
    deck.shuffleDeck();

    // Give each player a card
    for(size_t i = 0; i < players.size(); i++)
    {
        players[i]->drawCard();
    }

    // Remove a card from the game
    weakDiscard(deck.drawCard());

    // Player 1 starts
    int i = firstPlayer;
    int prevPlayer = -1;
    bool ongoing = true;

    // Play the Game!
    while(!deck.empty() && ongoing)
    {
        if(players[i]->isAlive())
        {
            // If only one player remains
            if(i == prevPlayer)
            {
                ongoing = false;
                break;
            }
            // Makes handmaiden wear off
            if(players[i]->isImmune())
            {
                players[i]->setImmunity(false);
            }
            cout << players[i]->getName() << "'s turn: \n";
            players[i]->drawCard();
            players[i]->showHand();
            // Checks for Countess Condition
            if(players[i]->hasCountessConditions())
            {
                cout << "You gotta play the Countess! Press anything to play the Countess" << endl;
                string str;
                cin >> str;
                // Force player to play Countess
                if(players[i]->getCurrCard()->getNum() == 7)
                    players[i]->playCurrCard();
                else
                    players[i]->playDrawnCard();
            }
            else
            {
                cout << "Type 1 to play the first card, 2 to play the second, "
                        "or any other number to get the description of the cards." << endl;
                int num;
                cin >> num;
                if(num == 1)
                    players[i]->playCurrCard();
                else if(num == 2)
                    players[i]->playDrawnCard();
                else
                {
                    players[i]->getCardDesc();
                    cout << endl;
                    cout << "Type 1 to play the first card or 2 to play the second. "
                            "(If you click anything else, I'm skipping you.)" << endl;
                    int num;
                    cin >> num;
                    if(num == 1)
                        players[i]->playCurrCard();
                    else if(num == 2)
                        players[i]->playDrawnCard();
                }
            }
            prevPlayer = i;
        }

        i++;
        if(i == players.size())
        {
            i = 0;
        }
    }

    // Determine Victor
    if(!ongoing)
    {
        cout << players[i]->getName() << " is the victor!" << endl;
        return i;
    }
    else
    {
        size_t currMax = 0;
        for(size_t i = 0; i < players.size(); i++)
        {
            if(players[i]->isAlive())
                players[i]->showCurrCard();
            else
                cout << players[i]->getName() << " is dead!" << endl;
            cout << endl;
            if(players[i]->isAlive() && players[i]->getCurrCardNum() > players[currMax]->getCurrCardNum())
                currMax = i;
        }
        cout << players[currMax]->getName() << " is the victor!" << endl;
        return currMax;
    }
}

Player* Game::findPlayer(const std::string& name)
{
    for(size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->getName() == name)
        {
            return players[i];
        }
    }
    return nullptr;
}

Card* Game::drawCard()
{
    return deck.drawCard();
}

void Game::discard(Card* card)
{
    card->discard(this);
    deck.discard(card);
}

void Game::weakDiscard(Card* card)
{
    deck.discard(card);
}

void Game::endGame()
{
    for(size_t i = 0; i < players.size(); i++)
    {
        players[i]->deleteInv();
    }
    deck.reset();
}

void Game::playFullGame()
{
    cout << "Let us begin a game of Love Letter. First to five wins wins the game!" << endl;
    cout << "Number of Players: " << players.size() << endl;
    for(size_t i = 0; i < players.size(); i++)
    {
        cout << players[i]->getName() << endl;
    }
    size_t winner = 0;
    wins = vector<int>(players.size());
    while(wins[winner] < 5)
    {
        cout << "Current Standings: " << endl;
        for(size_t i = 0; i < players.size(); i++)
        {
            cout << players[i]->getName() << ": " << wins[i] << endl;
        }
        winner = playGame(winner);
        wins[winner] += 1;
        resetPlayers();
    }
    cout << players[winner] << " is the winner of the game as they have won five rounds! Good Job!" << endl;
}

void Game::resetPlayers()
{
    for(size_t i = 0; i < players.size(); i++)
    {
        players[i]->reset();
    }
}