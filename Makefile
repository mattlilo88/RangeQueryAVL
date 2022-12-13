CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = wordrange.o wordrange_functions.o

wordrange: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o $@ wordrange.o wordrange_functions.o

wordrange.o: wordrange.cpp wordrange.h wordrange_functions.cpp
		$(CXX) -g $(CXXFLAGS) -c wordrange.cpp

wordrange_functions.o: wordrange_functions.cpp wordrange.h
		$(CXX) -g $(CXXFLAGS) -c wordrange_functions.cpp
	
clean:
	rm *.o
	rm wordrange