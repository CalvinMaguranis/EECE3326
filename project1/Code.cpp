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
#include <cstdlib>
#include <ctime>
#include "Exceptions.h"
#include "Code.h"

using namespace std;

/*
 * Mastermind secret code class
 * generates a random code of size n with range m and compares user input
 * to random code
 */

Code::Code(const vector<int>& v) : code(v), length(v.size()), used(v.size(), false) {}

Code::Code(const int n, const int m) : length(n) {
	// initialize our vectors
    vector<int> v(n, 0);
	vector<bool> used(n, false);

	// check input ranges are correct
    if (n <= 0 || m < 0) {
        throw BadInput("Code::Code - Cannot have a code length of 0 or a negative range!");
    }

    srand(time(0));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % m;
    }
    setCode(v);
}

// Compares guess to secret code and returns the number of correct digits
// in the correct locations.
int Code::checkCorrect(Code& guess) {
    const int secretCodeLength = getLength();
    int count = 0;
	vector<bool> correct(secretCodeLength, false);

	/// check vector lengths
    if (guess.getLength() != secretCodeLength) {
        throw InvalidVectSize("Code::checkCorrect - vectors are not the same length!");
    }

    for (int i = 0; i < guess.getLength(); i++) {
        if (getCode()[i] == guess.getCode()[i]) {
			// mark both the secret and guess code index values if used
			correct[i] = true;
			count++; 
		}
    }
	setUsed(correct);
	guess.setUsed(correct);
    return count;
}

// Compares guess to secret code and returns the number of correct digits
// in the incorrect locations.
int Code::checkIncorrect(Code& guess) {
    const int secretCodeLength = getLength();
    int count = 0; // correct digits in the incorrect location
	vector<bool> secretUsed = getUsed();
	vector<bool> guessUsed = guess.getUsed();
    
    /// check vector lengths
	if (guess.getLength() != secretCodeLength) {
		throw InvalidVectSize("Code::checkCorrect - vectors are not the same length!");
	}

	// compare all unused guess values to current unused secret code value
	for (int i = 0; i < secretCodeLength; i++) {
		for (int j = 0; j < guess.getLength(); j++) {
			if ((!secretUsed[i] && !guessUsed[j]) &&
				(getCode()[i] == guess.getCode()[j] )) {
				// we have a match, mark these indices as used and 
				// increase the count before continuing the compare
				secretUsed[i] = true;
				guessUsed[j] = true;
				count++;
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
