#ifndef WORDLIST_H
#define WORDLIST_H

class wordlist {
    public:
        wordlist(); // do nothing
        wordlist(string file);

        void open(string file);
        vector<string> wordlist::getDict() { return dict; }
    private:
        vector<string> dict;
};


#endif /* WORDLIST_H */