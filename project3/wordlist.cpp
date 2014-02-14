#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "d_except.h"

using namespace std;

wordlist::wordlist() {
}

wordlist::wordlist(string file) {
    open(file);
}

void wordlist::open(string file) {
    fstream ifs(file);
    string word;

    if (!ifs.is_open()) { 
        throw fileOpenError(file); 
    }

    while (getline(ifs, word)) {
        words.push_back(word);
    }

    ifs.close();
}