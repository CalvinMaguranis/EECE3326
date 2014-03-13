// Declarations and functions for project #4
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <vector>

using namespace std;

int numSolutions = 0;

// Stores the entire Sudoku board
class board {
public:
    board(int);
    void initialize(ifstream &);
    void print();
    void printConflicts();
    bool solve(long int &);
    bool isSolved();
private:
    int squareNumber(int, int);
    bool isBlank(int, int);
    int getCell(int, int);
    bool setCell(int, int, int);
    void clearCell(int, int);
    void clear();
    bool checkConflict(int, int, int);

    void findMostConstrainedBlankCell(int &, int &);

    // The following matrices go from 1 to boardSize in each
    // dimension.  I.e. they are each (boardSize+1) X (boardSize+1)
    int squareSize; // min
    int boardSize; // max
    matrix<int> value;
    vector< vector<bool> > rows;
    vector< vector<bool> > cols;
    vector< vector<bool> > sqs;
};

// Overloaded output operators for vector class.
ostream &operator<<(ostream &os, const vector<bool> &v) {
    for (vector<bool>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        os << " " << *ii;
    }
    return os;
}

ostream &operator<<(ostream &os, const vector< vector<bool> > &v) {
    for (vector< vector<bool> >::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        os << *ii << endl;
    }
    return os;
}

// Board constructor
board::board(int sqSize)
    : squareSize(sqSize),
      boardSize(squareSize *squareSize),
      value(boardSize, boardSize),
      rows(boardSize, vector<bool>(boardSize, false)),
      cols(boardSize, vector<bool>(boardSize, false)),
      sqs(boardSize,  vector<bool>(boardSize, false)) {
}

// Read a Sudoku board from the input file.
void board::initialize(ifstream &fin) {
    char ch;

    clear();
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            fin >> ch;

            // If the read char is not Blank
            if (ch != '.') {
                setCell(i, j, ch - '0'); // Convert char to int
            }
        }
    }
}

// Prints the current board.
void board::print() {
    for (int i = 0; i < boardSize; i++) {
        if (i % squareSize == 0) {
            cout << " -";
            for (int j = 0; j < boardSize; j++) {
                cout << "---";
            }
            cout << "-";
            cout << endl;
        }
        for (int j = 0; j < boardSize; j++) {
            if (j % squareSize == 0) {
                cout << "|";
            }
            if (!isBlank(i, j)) {
                cout << " " << getCell(i, j) << " ";
            } else {
                cout << "   ";
            }
        }
        cout << "|";
        cout << endl;
    }

    cout << " -";
    for (int j = 0; j < boardSize; j++) {
        cout << "---";
    }
    cout << "-";
    cout << endl;
}

void board::printConflicts() {
    cout << "Row Conflicts" << endl;
    cout << rows << endl;
    cout << "Column Conflicts" << endl;
    cout << cols << endl;
    cout << "Square Conflicts" << endl;
    cout << sqs << endl;
}

// cant set cells with conflicts so we only need to check that all
// board spaces have non-blank values
bool board::isSolved() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (getCell(i, j) == 0) {
                return false;
            }
        }
    }

    return true;
}

// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 0 to boardSize - 1
int board::squareNumber(int i, int j) {
    // Note that (int) i/squareSize and (int) j/squareSize are the x-y
    // coordinates of the square that i,j is in.
    return squareSize * (i / squareSize) + (j / squareSize);
}

// Returns true if cell i,j is blank, and false otherwise.
bool board::isBlank(int i, int j) {
    if (i < 0 || i >= boardSize || j < 0 || j >= boardSize) {
        cout << "i: " << i << " j: " << j << endl;
        throw rangeError("bad value in isBlank");
    }

    return (getCell(i, j) == 0);
}

// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
int board::getCell(int i, int j) {
    if (i >= 0 && i < boardSize && j >= 0 && j < boardSize) {
        return value[i][j];
    } else {
        cout << "i: " << i << " j: " << j << endl;
        throw rangeError("bad value in getCell");
    }
}

// Set the value into a cell (i,j).  Throws an exception
// if bad values are passed.
bool board::setCell(int i, int j, int val) {
    if (i >= 0 && i < boardSize &&
            j >= 0 && j < boardSize &&
            val >= 1 && val <= 9) {
        if (!checkConflict(i, j, val)) {
            rows[i].at(val - 1) = true;
            cols[j].at(val - 1) = true;
            sqs[squareNumber(i, j)].at(val - 1) = true;
            value[i][j] = val;

            return true;
        }

    } else {
        cout << "i: " << i << " j: " << j << " val: " << val << endl;
        throw rangeError("bad value in setCell");
    }
    return false;
}

void board::clearCell(int i, int j) {
    if (i >= 0 && i < boardSize &&
            j >= 0 && j < boardSize) {
        int val = getCell(i, j);
        if (val >= 1 && val <= 9) {
            rows[i].at(val - 1) = false;
            cols[j].at(val - 1) = false;
            sqs[squareNumber(i, j)].at(val - 1) = false;
            value[i][j] = 0;
        }
    } else {
        throw rangeError("bad value in clearCell");
    }
}

void board::clear() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            clearCell(i, j);
        }
    }
}

bool board::checkConflict(int i, int j, int v) {
    // if the number is already placed there, it is a conflict
    if (rows[i].at(v - 1) == true ||
            cols[j].at(v - 1) == true ||
            sqs[squareNumber(i, j)].at(v - 1) == true) {
        return true;
    }
    return false;
}

bool board::solve(long int &recursions) {
    int i, j;
    recursions++;
    if (isSolved()) {
        print();
        return true;
    }

    findMostConstrainedBlankCell(i, j);

    for (int val = 0; val < boardSize; val++) {
        if (setCell(i, j, val+1)) {
            if (solve(recursions)) {
                return true;
            }
        }
        clearCell(i, j); // reset cell
    }
    return false;
}

void board::findMostConstrainedBlankCell(int &minI, int &minJ) {
    int currentCount;
    int maxCount = 0;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (isBlank(i, j)) {
                currentCount = 0;
                for (int c = 0; c < boardSize; c++) {
                    if (rows[i][c] || cols[j][c] || sqs[squareNumber(i, j)][c]) {
                        currentCount++;
                    }
                }

                if (currentCount == 8) { // only 1 solution left
                    minI = i;
                    minJ = j;
                    return;
                }

                // least amount of solutions
                if (currentCount > maxCount) {
                    maxCount = currentCount;
                    minI = i;
                    minJ = j;
                }
            }
        }
    }
}

int main() {
    ifstream fin;
    int boardNum = 0;
    long int numRecursions = 0;
    // Read the sample grid from the file.
    string fileName = "sudoku.txt";

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try {
        board b1(3);

        while (fin && fin.peek() != 'Z') {
            boardNum++;
            b1.initialize(fin);
            b1.print();
            cout << endl;

            if (b1.solve(numRecursions)) {
                cout << "Solution found, ";
            }

            cout << " Num recursions: " << numRecursions << endl;
        }

        cout << "Avg recursions: " << (float) numRecursions / boardNum << endl;
    } catch  (indexRangeError &ex) {
        cout << ex.what() << endl;
        exit(1);
    } catch (rangeError &ex) {
        cout << ex.what() << endl;
        exit(1);
    }
}
