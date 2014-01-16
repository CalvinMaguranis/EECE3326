#include <iostream>
#include <vector>

using namespace std;

int main() {
    srand(time(NULL));
    return 1;
}

class Code {
    public:
        Code(const int, const int);
        int checkCorrect(const vector<int>) const;
        void print() const;
    private:
        vector<int> code;
};

Code::Code(const int n, const int m) : code(n, 0) {
    for (int i = 0; i < n; i++) {
        code[i] = rand() % m;
    }
}

int Code::checkCorrect(const vector<int> v) const {
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
        if (code[i] == v[i]) count++;
    }
    return count;
}

void Code::print() const {
    for (int i = 0; i < code.size(); i++) {
        cout << code[i] << ' ';
    }
    cout << endl;
}
