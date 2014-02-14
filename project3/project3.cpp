#include <time.h>
#include "d_matrix.h"
#include "d_except.h"
#include "grid.h"
#include "wordlist.h"

using namespace std;

// to preserve the direction we compare our strings in
enum DIRECTION { NONE = 0, UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

// forward declarations
void findMatches(grid g, wordlist words);
bool findWord(grid g, string word, int pos, int row, int col, DIRECTION d);
void setDirection(grid g, int &row, int &col, DIRECTION d);
bool neighbors(grid g, string word, int pos, int row, int col);
int mod(int a, int b);

int main() {
    try {
        time_t begin;
        time_t end;

        cout << "loading word list...";
        begin = time(0);
        wordlist list("wordlist.txt");
        end = time(0);
        cout << "completed (" << (end - begin) << " sec)" << endl;

        cout << "loading word matrix...";
        begin = time(0);
        grid g("input15.txt");
        end = time(0);
        cout << "completed (" << end - begin << " sec)" << endl;

        cout << "Starting search..." << endl;
        begin = time(0);
        findMatches(g, list);
        end = time(0);
        cout << "completed (" << end - begin << "sec)" << endl;
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

    system("PAUSE");
    return 0;
}

void findMatches(grid g, wordlist words) {
    vector<string> list = words.getList();

    int count = 0;
    for (vector<string>::iterator it = list.begin(); it != list.end(); ++it) {
        bool found = false;
        // access every word in the list
        for (int row = 0; row<g.getMatrix().rows(); row++) {
            // check every row in the matrix
            for (int col = 0; col<g.getMatrix().cols(); col++) {
                // and every column in the matrix
                found = findWord(g, *it, 0, row, col, NONE);
                if (found) {
                    cout << "Found: " << *it << endl;
                    break; // end search
                }
            }
            if (found) { break; } // break again...
        }
        count++;
        if (count % 2000 == 0) cout << "Checked: " << count << "/" << list.size() << endl;
    }
}

bool findWord(grid g, string word, int pos, int row, int col, DIRECTION d) {
    // check base cases
    if (word[pos] != g.getMatrix()[row][col]) {
        // mismatch found, continue to next row, col
        return false;
    }
    if ((word.size()-1) == pos) {
        // if we are at the end of the word
        return true;
    }

    if (d == NONE) {
        return neighbors(g, word, (pos + 1), row, col);
    } else {
        setDirection(g, row, col, d);
    }
    // go until we hit a base case
    return findWord(g, word, (pos + 1), row, col, d);
}

void setDirection(grid g, int &row, int &col, DIRECTION d) {
    switch (d) {
        case UP_LEFT:
            row = mod((row-1), g.getMatrix().rows());
            col = mod((col-1), g.getMatrix().cols());
            break;
        case UP:
            row = mod((row-1), g.getMatrix().rows());
            col = mod(col, g.getMatrix().cols());
            break;
        case UP_RIGHT:
            row = mod((row-1), g.getMatrix().rows());
            col = mod((col+1), g.getMatrix().cols());
            break;
        case LEFT:
            row = mod(row, g.getMatrix().rows());
            col = mod((col-1), g.getMatrix().cols());
            break;
        case RIGHT:
            row = mod(row, g.getMatrix().rows());
            col = mod((col+1), g.getMatrix().cols());
            break;
        case DOWN_LEFT:
            row = mod((row+1), g.getMatrix().rows());
            col = mod((col-1), g.getMatrix().cols());
            break;
        case DOWN:
            row = mod((row+1), g.getMatrix().rows());
            col = mod(col, g.getMatrix().cols());
            break;
        case DOWN_RIGHT:
            row = mod((row+1), g.getMatrix().rows());
            col = mod((col+1), g.getMatrix().cols());
            break;
        default:
            throw rangeError("A direction should be defined, logic/input corruption");
            break;
    }
}

bool neighbors(grid g, string word, int pos, int row, int col) {
    // check ALL neighbors for the next char,
    // there could be multiple chars of the same value
    if (findWord(g, word, pos,
                mod((row-1), g.getMatrix().rows()), mod((col-1), g.getMatrix().cols()),
                UP_LEFT)) {
        return true;
    }
    if (findWord(g, word, pos,
                mod((row-1), g.getMatrix().rows()), mod(col, g.getMatrix().cols()),
                UP)) {
        return true;
    }
    if (findWord(g, word, pos,
                mod((row-1), g.getMatrix().rows()), mod((col+1), g.getMatrix().cols()),
                UP_RIGHT)) {
        return true;
    }
    if (findWord(g, word, pos,
                mod(row, g.getMatrix().rows()), mod((col-1), g.getMatrix().cols()),
                LEFT)) {
        return true;
    }
    if (findWord(g, word, pos,
                mod(row, g.getMatrix().rows()), mod((col+1), g.getMatrix().cols()),
                RIGHT)) {
        return true;
    }
    if (findWord(g, word, pos,
                mod((row+1), g.getMatrix().rows()), mod((col-1), g.getMatrix().cols()),
                DOWN_LEFT)) {
        return true;
    }
    if (findWord(g, word, pos,
                mod((row+1), g.getMatrix().rows()), mod(col, g.getMatrix().cols()),
                DOWN)) {
        return true;
    }
    if (findWord(g, word, pos,
                mod((row+1), g.getMatrix().rows()), mod((col+1), g.getMatrix().cols()),
                DOWN_RIGHT)) {
        return true;
    }
    // none of the neighbors matched the word
    return false;
}

// helper wrap-around modulus function, from:
// http://stackoverflow.com/questions/4003232/how-to-code-a-modulo-operator-in-c-c-obj-c-that-handles-negative-numbers?rq=1
int mod(int a, int b)
{
    if (b == 0) { throw expressionError("Cannot perform modulus by 0!"); }
    if (b < 0) { return mod(-a, -b); }
    int ret = a % b;
    if (ret < 0) { ret += b; }
    return ret;
}
