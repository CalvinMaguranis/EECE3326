all: p3
	g++ project3.cpp grid.cpp wordlist.cpp -o p3

p3: project3.o grid.o wordlist.o
	g++ project3.o grid.o wordlist.o -o p3

project3.o: project3.cpp
	g++ -c project3.cpp

grid.o: grid.cpp
	g++ -c grid.cpp

wordlist.o: wordlist.cpp
	g++ -c wordlist.cpp

clean:
	rm -rf *o p3
