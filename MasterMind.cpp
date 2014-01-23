/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  Code.cpp
  Project #1b: Code class member function definitions
  Sam Coe
  Calvin Maguranis
 *****************************************************/
#include <iostream>
#include <vector>
#include "Code.h"

/*
 * Mastermind class
 * contains all necessary rules and objects to play the mastermind game
 */

// constructors
Mastermind::Mastermind() : secret(defaultLength, defaultRange),
                       length(defaultLength),
                       range(defaultRange){}

Mastermind::Mastermind(const int n, const int m) : secret(n, m),
                                                   length(n),
                                                   range(m){}

Code Mastermind::makeGuess() const {
    cout << "Make a guess for the secret code ";
    cout << "(code values range from 0 to " << range-1 << "): ";

    // store guess one value at a time
    vector<int> code(length, 0);
    for (int i = 0; i < length; i++) {
        int value;
        cin >> value;
        code[i] = value;
    }

    Code guess(code);
    cout << "Your guess is: ";
    cout << guess << endl;
    return guess;
}

void Mastermind::play() const {
    cout << "Secret code: " << secret << endl << endl;
    int guesses = 10;

    for (; guesses > 0; guesses--) {
        cout << "Guesses left: " << guesses << endl;
        Code guess = makeGuess();
        int correct = secret.checkCorrect(guess);
        if (correct == length) break;
        int incorrect = secret.checkIncorrect(guess);
        cout << "Numbers that are correct and in the correct position: " << correct << endl;
        cout << "Numbers that are correct and not in the incorrect position: " << incorrect << endl << endl;
    }

    if (guesses > 0) {
        cout << "You have won!" << endl;
    } else {
        cout << "You have lost!" << endl;
        cout << "The secret code was: " << secret << endl;
    }
}
