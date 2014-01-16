#include <iostream>
#include <vector>

using namespace std;

class Code {
    public:
        Code(const vector<int>&);
        Code(const int, const int);
        int checkCorrect(const Code&) const;
        void print() const;
    private:
        vector<int> getCode() const;
        void setCode(const vector<int>&);
        vector<int> code;
};

Code::Code(const vector<int>& v) : code(v) {}

Code::Code(const int n, const int m) {
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

vector<int> Code::getCode() const {
    return code;
}

void Code::setCode(const vector<int>& v) {
    code = v;
}

Code makeGuess() {
    int codeLength;
    cout << "Enter code length: ";
    cin >> codeLength;
    vector<int> code(codeLength, 0);
    for (int i = 0; i < codeLength; i++) {
        int value;
        cout << "Enter value (0-9): ";
        cin >> value;
        code[i] = value;
    }
    Code guess(code);
    cout << "Your guess is: ";
    guess.print();
    return guess;
}

int main() {
    srand(time(NULL));
    Code code(4, 10);
    cout << "Generated code: ";
    code.print();
    Code guess = makeGuess();
    int correct = code.checkCorrect(guess);
    cout << "Numbers correct: " << correct << endl;
    return 1;
}
