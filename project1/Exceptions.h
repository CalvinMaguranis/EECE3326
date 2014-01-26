/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  Exceptions.h
  Project #1b: Exceptions class declaration
  Sam Coe
  Calvin Maguranis
 *****************************************************/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>
using namespace std;

class BadInput : public exception {
	// definition taken from stdexcept.h exception derived classes
public:
	typedef exception exc;

	explicit BadInput(const string& what) : exc(what.c_str()) {}
	explicit BadInput(const char* what) : exc(what) {}
private:
};

class InvalidVectSize : public exception {
	// definition taken from stdexcept.h exception derived classes
public:
	typedef exception exc;

	explicit InvalidVectSize(const string& what) : exc(what.c_str()) {}
	explicit InvalidVectSize(const char* what) : exc(what) {}
private:
};

#endif /* EXCEPTIONS_H */