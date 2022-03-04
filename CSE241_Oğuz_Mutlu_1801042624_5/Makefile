CFLAGS=-c -Wall -Wextra -std=c++11

all : hex

hex : main.o abstracthex.o derVector.o oneD.o
	g++ main.o abstracthex.o derVector.o oneD.o -o hex

main.o : main.cpp
	g++ $(CFLAGS) main.cpp

abstracthex.o : abstracthex.cpp
	g++ $(CFLAGS) abstracthex.cpp

derVector.o : derVector.cpp
	g++ $(CFLAGS) derVector.cpp

oneD.o : derVector.cpp
	g++ $(CFLAGS) oneD.cpp
clean :
	rm -rf *o hex

