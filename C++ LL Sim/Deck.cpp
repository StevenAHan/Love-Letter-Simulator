#include <algorithm>
#include <random>
#include "Deck.h"
#include "Card.h"
#include <time.h>
using namespace std;


// Deck Class Code
Deck::Deck(int numOfPlayers)
{
    if(numOfPlayers > 4)
        expansion = true;
    else
        expansion = false;
}

void Deck::createDeck()
{
    reset();
    {
        // TODO
        if(expansion)
        {
            deckOfCards = vector<Card*>(21);
        }
            // Not Expansion
        else
        {
            deckOfCards = vector<Card*>(16);
            for(size_t i = 0; i < 5; i++)
                deckOfCards[i] = new Guard();
            deckOfCards[5] = new Priest();
            deckOfCards[6] = new Priest();
            deckOfCards[7] = new Baron();
            deckOfCards[8] = new Baron();
            deckOfCards[9] = new Handmaid();
            deckOfCards[10] = new Handmaid();
            deckOfCards[11] = new Prince();
            deckOfCards[12] = new Prince();
            deckOfCards[13] = new King();
            deckOfCards[14] = new Countess();
            deckOfCards[15] = new Princess();
        }
    }
}

void Deck::deleteDeck()
{
    for(size_t i = 0; i < deckOfCards.size(); i++)
    {
        delete deckOfCards[i];
        deckOfCards[i] = nullptr;
    }
    deckOfCards.clear();
}

void Deck::deleteDiscardPile()
{
    for(size_t i = 0; i < discardPile.size(); i++)
    {
        delete discardPile[i];
        discardPile[i] = nullptr;
    }
    discardPile.clear();
}

void Deck::reset()
{
    if(!deckOfCards.empty())
        deleteDeck();
    if(!discardPile.empty())
        deleteDiscardPile();
}

Card* Deck::drawCard()
{
    if(empty())
        return nullptr;
    Card* card = deckOfCards[deckOfCards.size() - 1];
    deckOfCards.pop_back();
    return card;
}

void Deck::shuffleDeck()
{
    srand(time(0));
    int val = rand() % 100;
    for(size_t i = 0;
        i < val; i++)
        random_shuffle(deckOfCards.begin(), deckOfCards.end());
}

const vector<Card*>& Deck::getDeck() const
{
    return deckOfCards;
}

bool Deck::empty() const
{
    return deckOfCards.empty();
}

void Deck::discard(Card* card)
{
    discardPile.push_back(card);
}