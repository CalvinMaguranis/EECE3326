#include <ctime>
#include "carddeck.h"
using namespace std;

deck::deck() {
    // seed random number generator
    srand(time(0));

    setCount(maxDeckSize);

    topCard = new node<card>(card(CLUB, 1));
    node<card> *curr = topCard;

    for (int i = 1; i < maxDeckSize; i++) {
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

// copy constructor
deck::deck(const deck& d) {
    // seed random number generator
    srand(time(0));

    *this = d;
}

deck::~deck() {
    node<card>* curr = getTopCard();
    node<card>* tmp;
    for (int i = 0; i < count; i++) {
        tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}

card deck::deal() {
    node<card> *top = getTopCard();
    if (top == NULL) { throw referenceError("Deck top card uninitialized!"); }
    card c = top->nodeValue;
    setTopCard(top->next);
    setCount(getCount() - 1);

    delete top;
    return c;
}

void deck::replace(card c) {
    // check range
    if ((c.getSuit() <= 0 || c.getSuit() >= 3) || (c.getValue() < 1 || c.getValue() > 13)) { // invalid 
        throw rangeError("Invalid card input!");
    }
    
    node<card>* prev;
    node<card>* curr = getTopCard();
    if (curr == NULL) { throw referenceError("Deck top card uninitialized!"); }

    // search if card already exists in deck,
    // if the card exists, remove it from it's position in the deck
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
        setCount(getCount() + 1); // added a new card to the deck
    } else {
        // found card in list move it to back
        prev->next = prev->next->next;
        while(prev->next != NULL) prev = prev->next;
        prev->next = curr;
    }
}

void deck::shuffle() {
    int count = getCount();
    int r = 0;
    card *a = new card[count];
    card tmp;
    node<card>* curr;

    // check for errors
    if (count > maxDeckSize) { throw rangeError("Deck size larger than allowed!"); }
    if (a == NULL) {
        throw memoryAllocationError("Failed to allocate shuffled value pointer a!");
    }

    // copy deck cards to pointer array a by value
    curr = getTopCard();
    for (int i = 0; i < count; i++) {
        a[i] = curr->nodeValue;
        curr = curr->next;
    }

    // fisher-yates shuffle algorithm on array
    for (int i = 0; i < count; i++) {
        if (&a[i] == NULL) {
            throw indexRangeError(
                    "Attempted to access uninitialized value in the array, fisher-yates shuffle",
                    i, count);
        }
        r = rand() % count;
        tmp = a[r];
        a[r] = a[i];
        a[i] = tmp;
    }

    // copy shuffled values to deck
    curr = getTopCard();
    for (int i = 0; i < count; i++) {
        if (&a[i] == NULL) { // in case anything has changed...
            throw indexRangeError(
                    "Attempted to access uninitialized value in the array, fisher-yates shuffle",
                    i, count);
        }
        curr->nodeValue = a[i];
        curr = curr->next;
    }

    delete[] a;
}

void deck::shuffle2() {
    int count = getCount();
    // create pointer array pointing to each node
    // pointer to pointer so cool
    node<card>** a = new node<card>*[count];

    // check for errors
    if (count > maxDeckSize) { throw rangeError("Deck size larger than allowed!"); }
    if (a == NULL) {
        throw memoryAllocationError("Failed to allocate memory for pointer array!");
    }

    // copy node pointers to array
    node<card>* curr = getTopCard();
    for (int i = 0; i < count; i++) {
        a[i] = curr;
        curr = curr->next;
    }

    // fisher-yates shuffle algorithm on array
    for (int i = 0; i < count; i++) {
        if (a[i] == NULL) {
            throw indexRangeError(
                    "Attempted to access uninitialized value in the array, fisher-yates shuffle",
                    i, count);
        }
        int r = rand() % count;
        node<card>* tmp = a[r];
        a[r] = a[i];
        a[i] = tmp;
    }

    // relink nodes in shuffled order
    curr = a[0];
    setTopCard(curr);
    for (int i = 1; i < count; i++) {
        if (a[i] == NULL) { // in case anything has changed...
            throw indexRangeError(
                    "Attempted to access uninitialized value in the array, fisher-yates shuffle",
                    i, count);
        }
        curr->next = a[i];
        curr = curr->next;
    }
    a[count-1]->next = NULL;
    delete[] a;
}

deck& deck::operator=(const deck& d) {
    if (this == &d) { return *this; }
    
    // check for input errors
    if (d.getCount() > maxDeckSize) { throw rangeError("Deck size is larger than max allowed"); }
    
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
    
    return *this;
}

card& card::operator=(const card& c) {
    if (this == &c) { return *this; }

    this->suit = c.getSuit();
    this->cardVal = c.getValue();
    return *this;
}
