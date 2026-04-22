CC=g++
CXXFLAGS=-O2 -std=gnu++17 -pipe -s -DNDEBUG

all: code

code: main.cpp
	$(CC) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f code
