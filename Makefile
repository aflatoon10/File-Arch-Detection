CC = g++  # compiler

all: Solution.cpp
	$(CC) -o solve Solution.cpp -I.

clean:
	rm solve
