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
		card() : suit(CLUB), cardVal(JOKER) {}
        card(const SUIT_TYPE s, const int c) : suit(s), cardVal(c) {};
        card(const card& c) : suit(c.getSuit()), cardVal(c.getValue()) {};

        // accessors
        SUIT_TYPE getSuit() const { return suit; }
        int getValue() const { return cardVal; }	

		// operator overloads
		card& operator=(const card& c);
    private:
        SUIT_TYPE suit;
        int cardVal;
};

// deck class definition
class deck {
    public:
		// constructors & destructors
        deck();
        deck(const deck&);
        ~deck();

		// accessors
        node<card> *getTopCard() const { return topCard; }

		// public member functions
        card deal();
        void replace(card c);
        void shuffle();

		// operator overloads
		deck& operator=(const deck& d);

    private:
		// private accessors
        void setTopCard(node<card>* c) { topCard = c; }
        int getCount() const { return count; }
        void setCount(int c) { count = c; }
        
		int count;
        node<card> *topCard;
};

#endif /* CARDDECK_H */
