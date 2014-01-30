#include "carddeck.h"

deck::deck() {
    int decksize = 52;

    topCard = new node<card>(card(CLUB, 1));
    node<card> *curr = topCard;

    for (int i = 1; i < decksize; i++) {
        int cardNum = i%13 + 1;
        SUIT_TYPE s;

        if (i < 13) { s = CLUB; }
        else if (i < 26) {s = DIAMOND;}
        else if (i < 39) {s = HEART;}
        else if (i < 52) {s = SPADE;}
        else { throw rangeError("Invalid deck size"); }

        curr->next = new node<card>(card(s, cardNum));
        curr = curr->next;
    }
}
