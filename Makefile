#Jack Lesemann, jwl4vg, pre-lab 11
CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall
DEBUG=-g

OBJECTS= topological.o 


topo: $(OBJECTS)
	$(CXX) $(DEBUG) $(OBJECTS) -o a.out
	
topological.o: topological.cpp



.PHONY: clean

clean:
	-rm -f *.out *.o *- topo    
