CXX ?=g++
CFLAGS=-c -Wall
NAVIO = ../../lib/Navio
INCLUDES = -I ../../lib/Navio

all:
	$(MAKE) -C ../../lib/Navio all
	$(CXX) -std=c++11 $(INCLUDES) gps.cpp -L$(NAVIO) -lnavio -o ../../bin/gps
	rm -rf *.o

clean:
	rm -rf *.o ../../bin/gps

