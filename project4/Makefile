all: p4
	g++ project4.cpp -o p4

p4: project4.o
	g++ project4.o -o p4

project4.o: project4.cpp
	g++ -c project4.cpp

clean:
	rm -rf *o p4
