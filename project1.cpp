/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  Project #1b
  Sam Coe
  Calvin Maguranis
 *****************************************************/
#include <iostream>
#include <vector>
#include "Code.h"
#include "MasterMind.h"

using namespace std;

/* global overloads */
// overload output operator for vectors
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << ' ';
    }
    return out;
}

int main() {
    int codeLength = 0;
    int codeRange = 0;

    srand(time(NULL));

    cout << "Enter code length: ";
    cin >> codeLength;
    cout << "Enter code value range: ";
    cin >> codeRange;
    cout << endl;

    if (codeLength > 0 || codeRange > 0) {
        Mastermind game;
        game.play();
    } else {
        Mastermind game(codeLength, codeRange);
        game.play();
    }

    return 1;
}
