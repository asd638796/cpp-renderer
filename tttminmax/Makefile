# Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Executables
EXECUTABLES = main.o board.o player.o

# Targets
all: $(EXECUTABLES)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -o main.o -c main.cpp

board.o: board.cpp
	$(CXX) $(CXXFLAGS) -o board.o -c board.cpp

player.o: player.cpp
	$(CXX) $(CXXFLAGS) -o player.o -c player.cpp

myprogram: $(EXECUTABLES)
	$(CXX) $(CXXFLAGS) -o myprogram $(EXECUTABLES)

clean:
	rm -f $(EXECUTABLES)