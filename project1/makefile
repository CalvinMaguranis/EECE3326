all: p1
	g++ project1.cpp Code.cpp MasterMind.cpp -o p1

p1: project1.o Code.o MasterMind.o 
	g++ project1.o Code.o MasterMind.o -o p1

project1.o: project1.cpp
	g++ -c project1.cpp

Code.o: Code.cpp
	g++ -c Code.cpp

MasterMind.o: MasterMind.cpp
	g++ -c MasterMind.cpp

clean:
	rm -rf *o p1
