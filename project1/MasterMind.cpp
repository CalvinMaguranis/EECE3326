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
#include "MasterMind.h"
#include "Code.h"
#include "Exceptions.h"
using namespace std;

/*
 * Mastermind class
 * contains all necessary rules and objects to play the mastermind game
 */

// constructors
Mastermind::Mastermind() : secret(defaultLength, defaultRange),
                       length(defaultLength),
                       range(defaultRange){}

Mastermind::Mastermind(const int codeLength, const int codeRange) :
                        secret(codeLength, codeRange),
                        length(codeLength),
                        range(codeRange) {}

void Mastermind::play() const {
    cout << "Secret code: " << secret << endl << endl;
    int guesses = 0;

    for (guesses = maxGuesses; guesses > 0; guesses--) {
        cout << "Guesses left: " << guesses << endl;
        Code guess = makeGuess();
        int correct = secret.checkCorrect(guess);
        if (correct == length) {
            // all guesses were correct!
            break;
        }

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

Code Mastermind::makeGuess() const {
    cout << "Make a guess for the secret code ";
    cout << "(code values range from 0 to " << range-1 << "): ";

    // store guess one value at a time
    vector<int> code(length, 0);
    int value = 0;
    for (int i = 0; i < length; i++) {
        cin >> value;
        if (value > range) {
            throw BadInput("MasterMind::makeGuess - Invalid value given, must be within 0 and given range!");
        }
        code[i] = value;
    }

    Code guess(code);
    cout << "Your guess is: ";
    cout << guess << endl;
    return guess;
}