# C++ compiler
CXX = g++

# some compiler flags
CXXFLAGS = -std=c++17 -g -Wall -O2

# targets to make
all: Integrate.x

Integrate.x: main.o Integral.o
	$(CXX) $(CXXFLAGS) main.o Integral.o -o Integrate.x

main.o: main.cpp Integral.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Integral.o: Integral.h Integral.cpp
	$(CXX) $(CXXFLAGS) -c Integral.cpp

# clean-up target (make clean)
clean:
	rm -f *.x
	rm -rf *.dSYM
	rm -f *.o
