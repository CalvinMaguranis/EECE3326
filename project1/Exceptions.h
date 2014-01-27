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
#include <iostream>

using namespace std;

class BadInput {
public:
	BadInput() : exc_msg("BadInput!") {}
	BadInput(const char* msg) : exc_msg(msg) {}

	const char* what() { return exc_msg; }
private:
	const char *exc_msg;
	
};

class InvalidVectSize {
public:
	InvalidVectSize() : exc_msg("InvalidVectSize!") {}
	InvalidVectSize(const char* msg) : exc_msg(msg) {}

	const char* what() { return exc_msg; }
private:
	const char *exc_msg;
	
};

#endif /* EXCEPTIONS_H */