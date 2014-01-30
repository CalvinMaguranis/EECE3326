all: p2
	g++ project2.cpp deck.cpp -o p2

p2: project2.o deck.o
	g++ project2.o deck.o -o p2

project2.o: project2.cpp
	g++ -c project2.cpp

deck.o: deck.cpp
	g++ -c deck.cpp

clean:
	rm -rf *o p2
