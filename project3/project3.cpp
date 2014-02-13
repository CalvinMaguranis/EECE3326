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

void findMatches(wordlist words, Grid g) {
    // loop through word list
    for(std::vector<string>::iterator it = words.words.begin(); it != words.words.end(); ++it) {
        bool found = findWord(*it, g);
        if (found) cout << *it;
    }
}

bool findWord(string word, Grid g) {
    // loop through grid
    matrix<char> m = g.getMatrix();
    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.cols(); j++) {
            bool found = findWordAtPos(word, 0, g, i, j, ANY);
            if (found) return true;
        }
    }
    return false;
}

bool findWordAtPos(string word, int pos, Grid g, int row, int col, DIRECTION) {
    // check for word at a position
    matrix<char> m = g.getMatrix();
    if (word[pos] != m[row][col]) {
        return false;
    }

    if (word.length()-1 == pos) {
        return true;
    }

    if (DIRECTION == ANY) {
        //check all adjacent characters
        bool a = findWord(word, pos+1, g, row-- % m.rows(), col, up);
        bool b = findWord(word, pos+1, g, row++ % m.rows(), col, down);
        bool c = findWord(word, pos+1, g, row, col-- % m.cols(), left);
        bool d = findWord(word, pos+1, g, row, col++ % m.cols(), right);
        bool e = findWord(word, pos+1, g, row--, col--, up-left);
        bool f = findWord(word, pos+1, g, row--, col++, up-right);
        bool g = findWord(word, pos+1, g, row++, col--, down-left);
        bool h = findWord(word, pos+1, g, row++, col++, down-right);
        if (a || b || c || d || e || f|| g || h) {
            return true;
        } else {
            return false;
        }
    } else {
        switch {
            case direction
                up
                    col-- % m.cols();
                    break;
                down
                    col++ % m.cols();
                    break;
                left
                    rows-- % m.rows();
                    break;
                right
                    rows++ % m.rows();
                    break;
                up-left
                    rows++ % m.rows();
                    break;
                up-right
                    rows++ % m.rows();
                    break;
                down-left
                    rows++ % m.rows();
                    break;
                down-right
                    rows++ % m.rows();
                    break;
        }

        return findWord(word, pos+1, g, row, col, direction);
    }
}
