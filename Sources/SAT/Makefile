CXX ?=g++
CFLAGS=-c -Wall
NAVIO = ../../lib/Navio
INCLUDES = -I ../../lib/Navio

all:
	$(MAKE) -C ../../lib/Navio all
	$(CXX) -std=c++11 $(INCLUDES) sat.cpp -L$(NAVIO) -lnavio -o ../../bin/sat
	rm -rf *.o

clean:
	rm -rf *.o ../../lib/Navio/Common
	rm -rf sat ../../bin/sat
