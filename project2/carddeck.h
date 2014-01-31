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



#endif /* CARDDECK_H */
