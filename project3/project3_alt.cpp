#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "d_except.h"
#include "d_matrix.h"

using namespace std;

class wordlist {
public:
	wordlist(); // do nothing
	wordlist(string file);

	void open(string file);
	string getWord();

private:
	vector<string> words;
};

wordlist::wordlist() {
}

wordlist::wordlist(string file) {
	open(file);
}

void wordlist::open(string file) {
	fstream ifs;
	string word;

	ifs.open(file.c_str());
	if (ifs.fail()) { throw fileOpenError("failed to open file"); }

	while (getline(ifs, word)) {
		words.push_back(word);
	}
}

string wordlist::getWord() {
	string word;
	if (words.empty()) {
		return "1";
	}
	word = words.back(); // get last word
	words.pop_back(); // remove from vector
	return word;
}

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