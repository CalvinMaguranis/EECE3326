#include "carddeck.h"

deck::deck() {
    int decksize = 52;

    topCard = new node<card>(card(CLUB, 1));
    node<card> *curr = topCard;

    for (int i = 1; i < decksize; i++) {
        int cardNum = i%13 + 1;
        SUIT_TYPE suit;

        if (i < 13) { suit = CLUB; }
        else if (i < 26) {suit = DIAMOND;}
        else if (i < 39) {suit = HEART;}
        else if (i < 52) {suit = SPADE;}
        else { throw rangeError("Invalid deck size"); }

        curr->next = new node<card>(card(suit, cardNum));
        curr = curr->next;
    }
}
