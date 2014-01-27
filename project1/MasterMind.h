/*****************************************************
  EECE3326 Optimization Methods
  Professor Waleed Meleis

  MasterMind.h
  Project #1b: MasterMind class declaration
  Sam Coe
  Calvin Maguranis
 *****************************************************/
#ifndef MASTERMIND_H
#define MASTERMIND_H
#include "Code.h"

using namespace std;

/*
 * Mastermind class
 * contains all necessary rules and objects to play the mastermind game
 */
class Mastermind {
    public:
        Mastermind();
        Mastermind(const int n, const int m);
        void play();
    private:
        Code makeGuess() const;
        Code secret;
        static const int defaultLength = 4;
        static const int defaultRange = 10;
        static const int maxGuesses = 10;
        const int length;
        const int range;
};

#endif /* MASTERMIND_H */