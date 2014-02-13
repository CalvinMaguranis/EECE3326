all: p3
	g++ project3.cpp -o p3

p3: project3.o
	g++ project3.o -o p3

project3.o: project3.cpp
	g++ -c project3.cpp

clean:
	rm -rf *o p3
