#ifndef CARDDECK_H
#define CARDDECK_H

#include <string>
#include <iostream>
#include "d_except.h"
#include "d_node.h"

using namespace std;

// public enumerations
enum SUIT_TYPE { CLUB, DIAMOND, HEART, SPADE };
enum FACE_CARDS { JOKER=0, ACE=1, KING=13, QUEEN=12, JACK=11 };

// card class definition
class card {
    public:
        // cards MUST be initialized with values
        card(const SUIT_TYPE s, const int c) : suit(s), cardVal(c) {};
        // accessors
        SUIT_TYPE getSuit() const { return suit; }
        int getValue() const { return cardVal; }
    private:
        const SUIT_TYPE suit;
        const int cardVal;
};

// deck class definition
class deck {
    public:
        deck();
        node<card> *getTopCard() const { return topCard;}
    private:
        node<card> *topCard;
};

// global print overload for card class
ostream& operator<<(ostream &ost, const card &c) {
    string suit;
    string face_card; // when we have Ace, King, Queen or, Jack

    // determine our suit
    if (c.getSuit() == CLUB) { suit = "Clubs"; }
    else if (c.getSuit() == DIAMOND) { suit = "Diamonds"; }
    else if (c.getSuit() == HEART) { suit = "Hearts"; }
    else if (c.getSuit() == SPADE) { suit = "Spades"; }
    else { throw rangeError("Invalid suit type"); }

    // determine if we have a face card
    if (c.getValue() >= 2 && c.getValue() <= 10) {
        // we have a normal value, just print it out and return
        ost << c.getValue() << " of " << suit;
    }
    else { // face card
        if (c.getValue() == JOKER) { face_card = "Joker"; }
        else if (c.getValue() == ACE) { face_card = "Ace"; }
        else if (c.getValue() == KING) { face_card = "King"; }
        else if (c.getValue() == QUEEN) { face_card = "Queen"; }
        else if (c.getValue() == JACK) { face_card = "Jack"; }
        else { throw rangeError("Card value out of range!"); } // catch an invalid card value
        ost << face_card << " of " << suit;
    }

    return ost;
}

// global print overload for deck class
ostream& operator<<(ostream &ost, const deck &d) {
    node<card>* curr = d.getTopCard();
    while (curr != NULL) {
        ost << curr->nodeValue;
        curr = curr->next;
    }
    return ost;
}

#endif /* CARDDECK_H */
