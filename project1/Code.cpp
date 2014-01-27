/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  Code.cpp
  Project #1a: Code class member function definitions
  Sam Coe
  Calvin Maguranis
 *****************************************************/
#include <iostream>
#include <vector>
#include <time.h>
#include "Exceptions.h"
#include "Code.h"

using namespace std;

/*
 * Mastermind secret code class
 * generates a random code of size n with range m and compares user input
 * to random code
 */

Code::Code(const vector<int>& v) : code(v), length(v.size()) {}

Code::Code(const int n, const int m) : length(n) {
    vector<int> v(n, 0);

    if (n <= 0 || m < 0) {
        throw BadInput("Code::Code - Cannot have a code length of 0 or a negative range!");
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % m;
    }
    setCode(v);
}

int Code::checkCorrect(const Code& guess) const {
    const int secretCodeLength = getLength();
    int count = 0;

    // check for errors
    if (guess.getLength() > secretCodeLength) {
        throw InvalidVectSize("Code::checkCorrect - Guess vector larger than secret code vector!");
    } else if (guess.getLength() < secretCodeLength) {
        throw InvalidVectSize("Code::checkCorrect - Secret code vector larger than guess code!");
    }

    for (int i = 0; i < guess.getLength(); i++) {
        if (getCode()[i] == guess.getCode()[i]) { count++; }
    }
    return count;
}

// Compares guess to secret code and returns the number of correct digits
// in the incorrect locations.
int Code::checkIncorrect(const Code& guess) const {
    const int secretCodeLength = getLength();
    int count = 0; // correct digits in the incorrect location
    vector<bool> used(secretCodeLength, false);

    // check for errors
    if (guess.getLength() > secretCodeLength) {
        throw InvalidVectSize("Code::checkIncorrect - Guess vector larger than secret code vector!");
    } else if (guess.getLength() < secretCodeLength) {
        throw InvalidVectSize("Code::checkIncorrect - Secret code vector larger than guess code!");
    }

    for (int i = 0; i < guess.getLength(); i++) { // loop over the guess
        for (int j = 0; j < secretCodeLength; j++) { // compare to secret code
            if(!used[j] && guess.getCode()[i] == getCode()[j]) {
                // digit not used, values are equal
                used[j] = true;

                if (i != j) {
                    // correct digit in the incorrect location
                    count++;
                }
                break;
            }
        }
    }
    return count;
}

void Code::print() const {
    vector<int> c = getCode();
    for (int i = 0; i < getLength(); i++) {
        cout << c[i] << ' ';
    }
    cout << endl;
}

// overload output operator for Code class
ostream& operator<<(ostream& out, const Code& c) {
    out << c.code;
    return out;
}
