#include <iostream>
#include <fstream>
#include "d_except.h"
#include "wordlist.h"
#include "quicksort.h"

using namespace std;

wordlist::wordlist(): minWordSize(5) {
}

wordlist::wordlist(string file): minWordSize(5) {
    open(file);
}

void wordlist::open(string file) {
    fstream ifs(file);
    string word;

    if (!ifs.is_open()) {
        throw fileOpenError(file);
    }

    while (getline(ifs, word)) {
        // ignore words smaller than 5 characters
        if (word.size() >= minWordSize) {
            list.push_back(word);
        }
    }

    // now sort the words
    quicksort(list, 0, list.size()-1);

    ifs.close();
}
