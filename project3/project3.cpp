#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "d_matrix.h"
#include "grid.h"
#include "wordlist.h"

using namespace std;

// to preserve the direction we compare our strings in
enum DIRECTION { NONE=0, UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

// declarations
bool checkAllNeighbors(Grid, string, int, int, int);
bool findWord(Grid, string, int, int, int, DIRECTION);

void findMatches(wordlist words, Grid g) {
    vector<string> list = words.getDict();
    matrix<char> m = g.getMatrix();
    // check every word in the list
    for(vector<string>::iterator it = list.begin(); it != list.end(); ++it) {
        bool found = false;
        // check every row in the matrix
        for (int row=0; row < m.rows(); row++) {
            // check every col in the matrix
            for (int col=0; col< m.cols(); col++) {
                found = findWord(g, *it, 0, row, col, NONE);
                if (found) {
                    cout << *it << endl;
                    break; // end search
                }
            }
            if (found) { break; }
        }
        if (found) { continue; } // go to next word
    }
}

bool findWord(Grid g, string word, int pos, int row, int col, DIRECTION d) {
    // check for word at a position
    matrix<char> m = g.getMatrix();
    if (word[pos] != m[row][col]) {
        return false;
    }

    if ((int)(word.length()-1) == pos) {
        return true;
    }

    if (d == NONE) {
        //check all adjacent characters
        return checkAllNeighbors(g, word, pos+1, row, col);
    } else {
        switch (d) {
            case UP:
                row = (row-1) % m.rows();
                break;
            case DOWN:
                row = (row+1) % m.rows();
                break;
            case LEFT:
                col = (col+1) % m.cols();
                break;
            case RIGHT:
                col = (col-1) % m.cols();
                break;
            case UP_LEFT:
                row = (row-1) % m.rows();
                col = (col+1) % m.cols();
                break;
            case UP_RIGHT:
                row = (row-1) % m.rows();
                col = (col-1) % m.cols();
                break;
            case DOWN_LEFT:
                row = (row+1) % m.rows();
                col = (col+1) % m.cols();
                break;
            case DOWN_RIGHT:
                row = (row+1) % m.rows();
                col = (col-1) % m.cols();
                break;
            default:
                //Error
                cout << "This shouldn't happen";
        }

        return findWord(g, word, pos+1, row, col, d);
    }
}

bool checkAllNeighbors(Grid g, string word, int pos, int row, int col) {
    //check all adjacent characters
    matrix<char> m = g.getMatrix();
    //TODO: The rows and cols need to be modulated still
    bool a = findWord(g, word, pos+1, row--, col, UP);
    bool b = findWord(g, word, pos+1, row++, col, DOWN);
    bool c = findWord(g, word, pos+1, row, col--, LEFT);
    bool d = findWord(g, word, pos+1, row, col++, RIGHT);
    bool e = findWord(g, word, pos+1, row--, col--, UP_LEFT);
    bool f = findWord(g, word, pos+1, row--, col++, UP_RIGHT);
    bool h = findWord(g, word, pos+1, row++, col--, DOWN_LEFT);
    bool i = findWord(g, word, pos+1, row++, col++, DOWN_RIGHT);
    if (a || b || c || d || e || f || h || i) {
        return true;
    } else {
        return false;
    }
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
