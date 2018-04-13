#CXX=g++47
CXXFLAGS=-std=c++11 -o
CXXCOMP=-std=c++11

.SUFFIXES: .x

.PHONY: clean


clean:
	rm -f *.o *.x core.* *.gch

proj5.x: proj5.cpp passserver.h  passserver.cpp hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) $@ $< -lcrypt passserver.cpp


	

