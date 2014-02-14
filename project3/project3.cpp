#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "d_matrix.h"

using namespace std;

// to preserve the direction we compare our strings in
enum DIRECTION { NONE=0, UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT }

void findMatches(wordlist words, Grid g) {
    vector<string> list = words.getList();
    bool found = false;
    for(vector<string>::iterator it = list.begin(); it != list.end(); ++it) {
        // access every word in the list
        for (int row=0; row<g.getMatrix.rows(); row++) {
            // check every row in the matrix
            for (int col=0; col<g.getMatrix.cols(); col++) {
                // check every row in the matrix
                found = findWord(*it, 0, g, row, col, NONE);
                if (found) { 
                    cout << *it << endl; 
                    break; // end search
                }
            }
            if (found) { break; }
        }
        if (found) { break; } // go to next word
    }
}

bool findWord(Grid g, string word, int pos, int row, int col, DIRECTION d) {
    // check base cases
    if (word[pos] != g.getMatrix()[row][col]) { 
        // mismatch found, continue to next row, col
        return false; 
    }
    if ((word.size() == pos) && (word[pos] != g.getMatrix()[row][col])) { 
        // if we are at the last word
        return true; 
    }

    if (d == NONE) { 
        return neighbors(g, word, &(pos+1), row, col, d,);

    } else {
        switch
            case direction
                UP
                    col-- % g.cols()
                down
                    col++ % g.cols()
                left
                    rows
                right
                    rows

        findWord(word, pos+1, g, row, col, direction);
    }
}

bool neighbors(Grid g, string word, int pos, int row, int col, DIRECTION d) {
    const int max_neighbors = 8; // any char will have 8 neighbors
    for (int i=0; i<max_neighbors; i++) {
        // check ALL neighbors for the next char, 
        // there could be multiple chars of the same value
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


