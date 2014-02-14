#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <vector>
using namespace std;

class wordlist {
    public:
        wordlist(); // do nothing
        wordlist(string file);

        void open(string file);
        vector<string> wordlist::getList() { return list; }
    private:
        vector<string> list;
};


#endif /* WORDLIST_H */