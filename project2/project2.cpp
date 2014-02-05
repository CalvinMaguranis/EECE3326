#include <iostream>
#include "carddeck.h"

using namespace std;

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
        ost << curr->nodeValue << endl;
        curr = curr->next;
    }
    return ost;
}

int main() {
    try {
        deck d;
        cout << d;
    } catch (rangeError &ex) {
        cout << ex.what() << endl;
        exit(0);
    } catch ( ... ) {
        cout << "unhandled exception found!" << endl;
        exit(0);
    }

    system("PAUSE");
    return 1;
}
