#include <iostream>
#include "carddeck.h"

using namespace std;

// global print overload for card class
ostream& operator<<(ostream &ost, const card &c) {
    // output card value
    if (c.getValue() >= 2 && c.getValue() <= 10) {
        // we have a normal value, just print it out and return
        ost << c.getValue() << " of ";
    }
    else if (c.getValue() == ACE) { ost << "Ace of "; }
    else if (c.getValue() == KING) { ost << "King of "; }
    else if (c.getValue() == QUEEN) { ost << "Queen of "; }
    else if (c.getValue() == JACK) { ost << "Jack of "; }
    else { throw rangeError("Card value out of range!"); } // catch an invalid card value

    // determine our suit
    if (c.getSuit() == CLUB) { ost << "Clubs"; }
    else if (c.getSuit() == DIAMOND) { ost << "Diamonds"; }
    else if (c.getSuit() == HEART) { ost << "Hearts"; }
    else if (c.getSuit() == SPADE) { ost << "Spades"; }
    else { throw rangeError("Invalid suit type"); }

    return ost;
}

// global print overload for deck class
ostream& operator<<(ostream &ost, const deck &d) {
    int count = 0;
    node<card>* curr = d.getTopCard();
    while (curr != NULL) {
        ost << curr->nodeValue;
        if ((count + 1) % 4 == 0) {
            // output 4 columns to make reading easier
            ost << endl;
        } else {
            ost << "\t";
        }
        curr = curr->next;
        count++;
    }
    ost << endl;
    return ost;
}

// play the game!
void playFlip() {
    deck d;
    card c;
    char inp;
    bool burn = false;
    int points = 0;
    int count = 0;

    // output header
    cout << "Welcome to the game of Flip!" << endl;
    cout << "============================" << endl << endl;

    // shuffle cards
    cout << "Shuffling cards...";
    for (int i = 0; i < 3; i++) {
        cout << "shuffle " << i+1 << "...";
        d.shuffle2();
    }
    cout << "complete!" << endl << endl;

    // get user input
    cout << "Burn the cards after use? (y/n) ";
    cin >> inp;
    if (inp != 'y' && inp != 'n') { throw rangeError("Invalid user input!"); }

    // set burn flag
    if (inp == 'y') { burn = true; }
    else if (inp == 'n') { burn = false; }
    inp = 'y';

    while (inp == 'y') {
        // take card
        cout << "Drawing card...";
        c = d.deal();
        cout << c << endl;

        // determine points
        if (c.getSuit() == HEART) {
            cout << "1 point extra for Heart suit, ";
            points += 1;
        }

        if (c.getValue() == ACE) {
            cout << "Ace, +10 points" << endl;
            points += 10;
        }
        else if (c.getValue() <= KING && c.getValue() >= JACK) {
            cout << "Face card, +5 points" << endl;
            points += 5;
        }
        else if (c.getValue() == 7) {
            cout << "Lose half your points" << endl;
            points = points / 2;
        }
        else if (c.getValue() <= 6 && c.getValue() >= 2) {
            cout << "Lose all your points" << endl;
            points = 0;
        }
        else {
            cout << "Neutral card drawn, points are untouched" << endl;
        }
        cout << "Points: " << points;

        // if not burning the cards, place the
        // top card to the bottom of the deck
        if (!burn) { 
            d.replace(c); 
            count++;
            if ((count%52)==0) { 
                d.shuffle2(); 
                count = 0; 
                cout << "All cards have been taken, shuffling!" << endl;
                }
        } else {
            if (!burn && d.getCount() == 0) {
                cout << endl << endl << "All cards have been taken!" << endl << endl;
                break;
            } else {
                cout << ", " << d.getCount() << " cards remaining.";
            }
        }
        cout << endl << endl;

        // ask to take another card
        cout << "Take another card? (y/n) ";
        cin >> inp;
        if (inp != 'y' && inp != 'n') { throw rangeError("Invalid user input!"); }
        cout << endl;
    }

    cout << "Finished the game with " << points << " points!" << endl;
}

int main() {
    try {
        playFlip();
    }
    catch (rangeError &ex) {
        cout << ex.what() << endl;
        exit(0);
    }
    catch (referenceError &ex) {
        cout << ex.what() << endl;
        exit(0);
    }
    catch (indexRangeError &ex) {
        cout << ex.what() << endl;
        exit(0);
    }
    catch (memoryAllocationError &ex) {
        cout << ex.what() << endl;
        exit(0);
    }
    catch ( ... ) {
        cout << "unhandled exception found!" << endl;
        exit(0);
    }

    system("PAUSE");
    return 1;
}
