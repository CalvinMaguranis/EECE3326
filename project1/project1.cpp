/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  Project #1b
  Sam Coe
  Calvin Maguranis
 *****************************************************/
#include <iostream>
#include <vector>
#include "MasterMind.h"
#include "Exceptions.h"
using namespace std;

// overload output operator for vectors
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << ' ';
    }
    return out;
}

// overload output operator for Code class
ostream& operator<<(ostream& out, const Code& c) {
	out << c.code;
	return out;
}

int main() {
    int codeLength = 0;
    int codeRange = 0;
	int wait = 0;

    cout << "Enter code length: ";
    cin >> codeLength;
    cout << "Enter code value range: ";
    cin >> codeRange;
    cout << endl;

    try {
        if (codeLength > 0 && codeRange >= 0) {
            Mastermind game(codeLength, codeRange);
            game.play();
        } else {
            Mastermind game;
            game.play();
        }
    } catch (BadInput &ex) {
        cout << "Bad input: " << ex.what() << endl;
		exit(0);
    } catch (InvalidVectSize &ex) {
        cout << "Invalid vector size: " << ex.what() << endl;
		exit(0);
    } catch ( ... ) {
        cout << "Unhandled exception found!" << endl;
		exit(0);
    }

	system("PAUSE");
    return 1;
}
