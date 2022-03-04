CFLAGS=-c -Wall -Wextra -std=c++11

all : hex

hex : main.o function.o 
	g++ main.o function.o -o hex

main.o : main.cpp
	g++ $(CFLAGS) main.cpp

funtion.o : function.cpp
	g++ $(CFLAGS) function.cpp
clean :
	rm -rf *o hex

