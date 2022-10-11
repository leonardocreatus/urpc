CC = g++
CFLAGS = -std=c++17 -c -O2 -Wall 
LD = ld

all:
	$(CC) $(CFLAGS) main.cpp model.cpp coding.cpp

	$(CC) -o app coding.o model.o main.o

clean:
	rm -rf *.o app

