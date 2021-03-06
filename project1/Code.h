/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  Code.h
  Project #1a: Code class declaration
  Sam Coe
  Calvin Maguranis
 *****************************************************/
#ifndef CODE_H
#define CODE_H
#include <vector>
#include <iostream>

using namespace std;

/*
 * Mastermind secret code class
 * generates a random code of size n with range m and compares user input
 * to random code
 */
class Code {
	public:
        // constructors allow for either generating the random code or
        // inputing a pre-defined code
        Code(const vector<int>& v);
        Code(const int n, const int m);

        // accessors
        vector<int> getCode() const { return code; }
		vector<bool> getUsed() const { return used; }
		void setUsed(const vector<bool> &v) { used = v; }
		int getLength() const { return length; }

        int checkCorrect(Code&);
        int checkIncorrect(Code&);
        void print() const;

        // overloaded output operator
        friend ostream& operator<<(ostream&, const Code&);

    private:
        void setCode(const vector<int> &v) { code = v; }
		
        vector<int> code;
		vector<bool> used;
        const int length;
};

#endif /* CODE_H */