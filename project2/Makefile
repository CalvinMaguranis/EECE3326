all: p2
	g++ project2.cpp carddeck.cpp -o p2

p2: project2.o carddeck.o
	g++ project2.o carddeck.o -o p2

project2.o: project2.cpp
	g++ -c project2.cpp

carddeck.o: carddeck.cpp
	g++ -c carddeck.cpp

clean:
	rm -rf *o p2
