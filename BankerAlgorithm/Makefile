CC = g++
CPPFLAGS = -g -Wall
all: main
main: main.o Resource.o
main.o: main.cpp
Resource.o: Resource.hpp Resource.cpp
clean:
	rm -f *.o main
