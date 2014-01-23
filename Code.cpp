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

/*
 * Mastermind secret code class
 * generates a random code of size n with range m and compares user input
 * to random code
 */

Code::Code(const vector<int>& v) : code(v), length(v.size()) {}

Code::Code(const int n, const int m) : length(n) {
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
        v[i] = rand() % m;
    }
    setCode(v);
}

int Code::checkCorrect(const Code& guess) const {
    int count = 0;
    for (int i = 0; i < guess.getLength(); i++) {
        if (getCode()[i] == guss.getCode()[i]) count++;
    }
    return count;
}

// Compares guess to secret code and returns the number of correct digits
// in the incorrect locations.
int Code::checkIncorrect(const Code& guess) const {
    const int secretCodeLenght = getLength();
    int count = 0; // correct digits in the incorrect location
    vector<bool> used(getLength(), false);

    for (int i = 0; i < guess.getLength(); i++) { // loop over the guess
        for (int j = 0; j < secretCodeLenght; j++) { // compare to secret code
            if(!used[j] && guess.getCode()[i] == getCode()[j]) {
                used[j] = true;
                // correct digit in the incorrect location
                if (i != j) { count++; }
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
