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
        vector<string> getList() { return list; }
        vector<string> getValid() { return valid; }
        const int getMinWordSize() { return minWordSize; }
    private:
        vector<string> list;
        vector<string> valid;
        const int minWordSize;
};


#endif /* WORDLIST_H */
