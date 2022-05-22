#ifndef LOVELETTERSIM_DECK_H
#define LOVELETTERSIM_DECK_H
#include <iostream>
#include <string>
#include<vector>


class Card;

class Deck {
public:

    Deck(int numOfPlayers);

    void createDeck();

    void deleteDeck();

    void deleteDiscardPile();

    void reset();

    void shuffleDeck();

    Card* drawCard();

    void discard(Card* card);

    bool empty() const;

    const std::vector<Card*>& getDeck() const;


//private:
    std::vector<Card*> deckOfCards;
    std::vector<Card*> discardPile;
    bool expansion;
};


#endif //LOVELETTERSIM_DECK_H