#Makefile
all: add-nbo

add-nbo: add.o main.o
	g++ -o add-nbo add.o main.o

main.o: add.h main.c
	g++ -c -o main.o main.cpp

add.o: add.h add.cpp
	g++ -c -o add.o add.cpp

clean:
	rm -f add-nbo
	rm -f *.o
