#ifndef CARDDECK_H
#define CARDDECK_H

#include <iostream>
#include "d_except.h"
#include "d_node.h"

// public enumerations
enum SUIT_TYPE { CLUB, DIAMOND, HEART, SPADE };
enum FACE_CARDS { JOKER=0, ACE=1, KING=13, QUEEN=12, JACK=11 };

// card class definition
class card {
    public:
        // cards MUST be initialized with values
        card(const SUIT_TYPE s, const int c) : suit(s), cardVal(c) {};
        card(const card& c) : suit(c.getSuit()), cardVal(c.getValue()) {};
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
        deck(const deck&);
        ~deck();
        node<card> *getTopCard() const { return topCard; }
        card deal();
        void replace(card c);
        void shuffle();
    private:
        void setTopCard(node<card>* c) { topCard = c; }
        int getCount() const { return count; }
        void setCount(int c) { count = c; }
        int count;
        node<card> *topCard;
};

#endif /* CARDDECK_H */
