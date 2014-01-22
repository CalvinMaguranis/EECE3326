/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  Project #1b
  Sam Coe
  Calvin Maguranis
 *****************************************************/

#include <iostream>
#include <vector>

using namespace std;

/*
 * Mastermind secret code class
 * generates a random code of size n with range m and compares user input
 * to random code
 */
class Code {
    public:
        // constructors allow for either generating the random code or
        // inputing a pre-defined code
        Code(const vector<int>&);
        Code(const int, const int);

        // accessors
        vector<int> getCode() const { return code; }
        int getLength() const { return length; }

        int checkCorrect(const Code&) const;
        int checkIncorrect(const Code&) const;
        void print() const;

        // overloaded output operator
        friend ostream& operator<<(ostream&, const Code&);

    private:
        void setCode(const vector<int> &v) { code = v; }

        vector<int> code;
        const int length;
};

/* Code class member function definitions */
Code::Code(const vector<int>& v) : code(v), length(v.size()) {}

Code::Code(const int n, const int m) : length(n) {
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
        v[i] = rand() % m;
    }
    setCode(v);
}

int Code::checkCorrect(const Code& c) const {
    int count = 0;
    for (int i = 0; i < c.getLength(); i++) {
        if (getCode()[i] == c.getCode()[i]) count++;
    }
    return count;
}

int Code::checkIncorrect(const Code& c) const {
    int count = 0;
    vector<bool> used(getLength(), false);
    for (int i = 0; i < c.getLength(); i++) {
        for (int j = 0; j < getLength(); j++) {
            if(!used[j] && c.getCode()[i] == getCode()[j]) {
                used[j] = true;
                if (i != j) {
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

// overload output operator for vectors
template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        out << v[i] << ' ';
    }
    return out;
}

ostream& operator<<(ostream& out, const Code& c) {
    out << c.code;
    return out;
}

class Mastermind {
    public:
        Mastermind();
        Mastermind(const int n, const int m);
        void play() const;
    private:
        Code makeGuess() const;
        const Code secret;
        static const int defaultLength = 4;
        static const int defaultRange = 10;
        const int length;
        const int range;
};

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
