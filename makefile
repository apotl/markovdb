CC=g++ -Wall

all: markovdb

markovdb: db.o fragment.o
	$(CC) -o markovdb main.cpp db.o fragment.o

db.o: db.hpp db.cpp
	$(CC) -c db.cpp

fragment.o: fragment.hpp fragment.cpp
	$(CC) -c fragment.cpp

tidy :
	rm -f db.o

clean :
	rm -f db.o fragment.o markovdb
