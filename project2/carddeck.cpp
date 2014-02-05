#include "carddeck.h"

deck::deck() {
    int decksize = 52;
    setCount(decksize);

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

deck::deck(const deck& d) {
    // perform deep copy on deck cards
    setCount(d.getCount());
    if (d.getTopCard() == NULL) {
        setTopCard(NULL);
    } else {
        node<card>* oCurr = d.getTopCard();
        node<card>* curr = new node<card>(card(oCurr->nodeValue));
        setTopCard(curr);
        for (int i = 0; i < count; i++) {
            curr->next = new node<card>(card(oCurr->next->nodeValue));
            curr = curr->next;
            oCurr = oCurr->next;
        }
    }
}

deck::~deck() {
    node<card>* curr = getTopCard();
    for (int i = 0; i < count; i++) {
        node<card>* old = curr;
        curr = curr->next;
        delete old;
    }
}

card deck::deal() {
    node<card> *top = getTopCard();
    card c = top->nodeValue;
    setTopCard(top->next);
    setCount(getCount() - 1);
    delete top;
    return c;
}

void deck::replace(card c) {
    node<card>* prev;
    node<card>* curr = getTopCard();
    for (int i = 0; i < count; i++) {
        if (curr->nodeValue.getSuit() == c.getSuit() &&
            curr->nodeValue.getValue() == c.getValue()) {
            break;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (curr == NULL) {
        // reached end of list without finding card
        prev->next = new node<card>(card(c));
    } else {
        // found card in list move it to back
        prev->next = prev->next->next;
        while(prev->next != NULL) prev = prev->next;
        prev->next = curr;
    }
}

void deck::shuffle() {
    // seed random number generator
    srand(time(0));

    // create pointer array pointing to each node
    node<card>* a[count];
    node<card>* curr = getTopCard();
    for (int i = 0; i < count; i++) {
        a[i] = curr;
        curr = curr->next;
    }

    // fisher-yates shuffle algorithm on array
    for (int i = 0; i < count; i++) {
        int r = rand() % count;
        node<card>* tmp = a[r];
        a[r] = a[i];
        a[i] = tmp;
    }

    // relink cards to create shuffled deck
    curr = a[0];
    for (int i = 1; i < count; i++) {
        curr->next = a[i];
        curr = curr->next;
    }

    // set top card to beginning of shuffled deck
    setTopCard(a[0]);
}

deck& deck::operator=(const deck& d) {
    if (this == &d) return *this;
    //TODO: copy deck from old to new not just the pointer
    return *this;
}

//TODO: How to overcome const data members
card& card::operator=(const card& c) {
    if (this == &c) return *this;
    //suit = c.getSuit();
    //cardVal = c.getValue();
    return *this;
}
