#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "d_matrix.h"

using namespace std;

class Grid {
    public:
        Grid();
        matrix<char> getMatrix();
        void setMatrix(matrix<char>);
        void setMatrix(string);
    private:
        matrix<char> m;
};

Grid::Grid() : m(matrix<char>()) {}

matrix<char> Grid::getMatrix() {
    return m;
}

void Grid::setMatrix(matrix<char> nm) {
    m = nm;
}

void Grid::setMatrix(string s) {
    ifstream f(s, ios::in);
    if (f.is_open()) {
        int rows, cols;
        f >> rows >> cols;
        m.resize(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                f >> m[i][j];
            }
        }
        f.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

class wordlist {
    public:
        wordlist(); // do nothing
        wordlist(string file);

        void open(string file);
        string getWord();

    private:
        vector<string> words;
};

wordlist::wordlist() {
}

wordlist::wordlist(string file) {
    open(file);
}

void wordlist::open(string file) {
    fstream ifs;
    string word;

    ifs.open(file.c_str());
    if (ifs.fail()) { throw fileOpenError("failed to open file"); }

    while (getline(ifs, word)) {
        words.push_back(word);
    }
}

string wordlist::getWord() {
    string word;
    if (words.empty()) {
        return "1";
    }
    word = words.back(); // get last word
    words.pop_back(); // remove from vector
    return word;
}

/*
int main() {
    try {
        string word;
        wordlist mlist("wordlist.txt");
        while (word != "1") {
            word = mlist.getWord();
            if (word != "1") { cout << word << endl; }
        }

    } catch (fileOpenError &ex) {
        cout << ex.what() << endl;
    } catch (underflowError &ex) {
        cout << ex.what() << endl;
    } catch (...) {
        cout << "unknown exception" << endl;
    }

    return 0;
}
*/

int main() {
    Grid g;
    g.setMatrix("input15.txt");
    matrix<char> m = g.getMatrix();
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}

void findMatches(vector<string> words, Grid g) {
    for(std::vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
        bool found = findWord(*it, g, 0, 0, DIRECTION);
        if (found) cout << *it;
    }
}

bool findWord(string word, Grid g, int row, int col, DIRECTION) {

}
