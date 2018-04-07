#CXX=g++47
CXXFLAGS=-std=c++11 -o

.SUFFIXES: .x

.PHONY: clean


clean:
	rm -f *.o *.x core.* *.gch

proj5.x: hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) $@ $<