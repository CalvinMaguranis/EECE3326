#include <iostream>
#include <sstream>
#include <time.h>
#include <math.h>
#include "d_matrix.h"
#include "d_except.h"
#include "grid.h"
#include "wordlist.h"

using namespace std;

#define ERR -1

// to preserve the direction we compare our strings in
enum DIRECTION { UP = 0, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };
const int POSSIBLE_DIRECTIONS = 8;
vector<string> valid;

void findMatches(grid &g, wordlist &l);
void searchMatrix(grid &g, wordlist &l, int row, int col);
string getWord(grid &g, wordlist &l, int row, int col, int wordSize, DIRECTION d);
int binSearch(wordlist &l, string key);
void incrementDirection(grid &g, DIRECTION d, int &row, int &col);
int mod(int a, int b);


int main() {
    try {
        time_t begin;
        time_t end;

        string wlist, sGrid;

        cout << "Wordlist location: ";
        cin >> wlist;
        cout << "Search grid location: ";
        cin >> sGrid;
        cout << endl << endl;

        cout << "loading word list...";
        begin = time(0);
        wordlist list(wlist);
        end = time(0);
        cout << "completed (" << (end - begin) << " sec)" << endl;
        cout << "size: " << list.getList().size() << endl;

        cout << "loading word matrix...";
        begin = time(0);
        grid g(sGrid);
        end = time(0);
        cout << "completed (" << end - begin << " sec)" << endl;

        cout << "Starting search..." << endl;
        begin = time(0);
        findMatches(g, list);
        end = time(0);
        cout << "completed (" << end - begin << "sec)" << endl;

        cout << "Words found: " << endl;
        for (int i = 0; i < valid.size(); i++) {
            cout << valid[i] << endl;
        }
    } catch (fileOpenError &ex) {
        cout << ex.what() << endl;
    } catch (underflowError &ex) {
        cout << ex.what() << endl;
    } catch (rangeError &ex) {
        cout << ex.what() << endl;
    } catch (expressionError &ex) {
        cout << ex.what() << endl;
    } catch (...) {
        cout << "unknown exception" << endl;
    }

    //system("PAUSE");
    return 0;
}

void findMatches(grid &g, wordlist &l) {
    int maxRows = g.getMatrix().rows();
    int maxCols = g.getMatrix().cols();
    int hyp = sqrt((pow(maxRows, 2) + pow(maxCols, 2))); // integer automatically floors
    int maxWordSize = hyp;
    int minWordSize = l.getMinWordSize();

    int r, c;

    for (int row = 0; row < maxRows; row++) {
        for (int col = 0; col < maxCols; col++) {
            // check all possible words in all directions
            for (int d = 0; d < POSSIBLE_DIRECTIONS; d++) {
                // set starting point
                ostringstream os;
                r = row;
                c = col;

                for (int i = 0; i < maxWordSize; i++) {
                    os << g.getMatrix()[r][c];
                    incrementDirection(g, (DIRECTION)d, r, c);
                    if (i >= (minWordSize - 1)) {
                        if (binSearch(l, os.str()) != ERR) {
                            //cout << "found match: " << os.str() << endl;
                            valid.push_back(os.str());
                        }
                    }
                } // end getting words in a set direction
            } // end searching in all directions
            //cout << "Total words found (" << row << ", " << col << "): ";
            //cout << valid.size() << endl;
        } // end cols
    } // end rows
}

void incrementDirection(grid &g, DIRECTION d, int &row, int &col) {
    switch (d) {
        case UP_LEFT:
            row = mod((row - 1), g.getMatrix().rows());
            col = mod((col - 1), g.getMatrix().cols());
            break;
        case UP:
            row = mod((row - 1), g.getMatrix().rows());
            col = mod(col, g.getMatrix().cols());
            break;
        case UP_RIGHT:
            row = mod((row - 1), g.getMatrix().rows());
            col = mod((col + 1), g.getMatrix().cols());
            break;
        case LEFT:
            row = mod(row, g.getMatrix().rows());
            col = mod((col - 1), g.getMatrix().cols());
            break;
        case RIGHT:
            row = mod(row, g.getMatrix().rows());
            col = mod((col + 1), g.getMatrix().cols());
            break;
        case DOWN_LEFT:
            row = mod((row + 1), g.getMatrix().rows());
            col = mod((col - 1), g.getMatrix().cols());
            break;
        case DOWN:
            row = mod((row + 1), g.getMatrix().rows());
            col = mod(col, g.getMatrix().cols());
            break;
        case DOWN_RIGHT:
            row = mod((row + 1), g.getMatrix().rows());
            col = mod((col + 1), g.getMatrix().cols());
            break;
        default:
            throw rangeError("A direction should be defined, logic/input corruption");
            break;
    }
}

// finds and returns index of found search, -1 for not found
int binSearch(wordlist &l, string key) {
    int min = 0;
    int max = l.getList().size() - 1;
    if (max < min) {
        throw rangeError("Binary Search: Cannot have a min larger than max!");
    }
    string val;
    int err = -1;
    int mid;

    while (max > min) {
        mid = min + (max - min) / 2;
        val = l.getList()[mid];

        if (key.compare(val) == 0) {
            return mid;
        } else if (key.compare(val) < 0) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }
    return err;
}

// helper wrap-around modulus function, from:
// http://stackoverflol.com/questions/4003232/how-to-code-a-modulo-operator-in-c-c-obj-c-that-handles-negative-numbers?rq=1
int mod(int a, int b) {
    if (b == 0) {
        throw expressionError("Cannot perform modulus by 0!");
    }
    if (b < 0) {
        return mod(-a, -b);
    }
    int ret = a % b;
    if (ret < 0) {
        ret += b;
    }
    return ret;
}
