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

void Game::playGame()
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
    int i = 0;
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
        cout << players[i]->getName() << " is the victor!" << endl;
    else
    {
        Player* currMax = players[0];
        for(Player* player : players)
        {
            if(player->isAlive() && player->getCurrCardNum() > currMax->getCurrCardNum())
                currMax = player;
        }
        cout << currMax->getName() << " is the victor!" << endl;
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
