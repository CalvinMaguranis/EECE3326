#include <iostream>
#include <vector>

using namespace std;

/* MasterMind secret code class
    generates a random code of size n with range m and compares user input
    to random code
*/
class Code {
    public:
        // constructors allow for either generating the random code or
        // inputing a pre-defined code
        Code(const vector<int>&);
        Code(const int n, const int m);

        // accessors
        vector<int> getCode() const { return code; }
        void setCode(const vector<int> &v) { code = v; }
        int getLength() const { return length; }
        int getRange() const { return range; }

        int checkCorrect(const Code&) const;
        void print() const;
    private:
        vector<int> code;
        const int length;
        const int range;
};

/* Code class member function definitions */
Code::Code(const vector<int>& v) : code(v), length(v.size()), range(0) {}

Code::Code(const int n, const int m) : length(n), range(m) {
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
        v[i] = rand() % m;
    }
    setCode(v);
}

int Code::checkCorrect(const Code& c) const {
    int count = 0;
    for (int i = 0; i < c.getCode().size(); i++) {
        if (getCode()[i] == c.getCode()[i]) count++;
    }
    return count;
}

void Code::print() const {
    vector<int> c = getCode();
    for (int i = 0; i < c.size(); i++) {
        cout << c[i] << ' ';
    }
    cout << endl;
}

// prompt for secret code guess
// note: separated from main for easier integration in the following projects
Code makeGuess(const int len, const int range) {
    cout << "Make a guess for the secret code ";
    cout << "(code values range from 0 to " << range << "): ";

    // store guess one value at a time
    vector<int> code(len, 0);
    for (int i = 0; i < len; i++) {
        int value;
        cin >> value;
        code[i] = value;
    }

    Code guess(code);
    cout << "Your guess is: ";
    guess.print();
    return guess;
}

int main() {
    int codeLength = 0;
    int codeRange = 0;
    int correct = 0;

    cout << "Enter code length: ";
    cin >> codeLength;
    cout << "Enter code value range: ";
    cin >> codeRange;
    cout << endl << endl;

    Code code(codeLength, codeRange);
    srand(time(NULL));
    cout << "Generated code: ";
    code.print();

    Code guess = makeGuess(code.getLength(), code.getRange());
    correct = code.checkCorrect(guess);
    cout << "Numbers correct: " << correct << endl;

    return 1;
}
