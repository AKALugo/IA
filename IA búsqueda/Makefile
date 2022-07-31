CXX = g++
CXXFLAGS = -std=c++14 -g -Wall
DEPS = world.hpp cell.hpp heuristica.hpp
OBJ = world.o main.o cell.o

%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm main *.o