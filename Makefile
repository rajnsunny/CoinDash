CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./src
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

platformer: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f src/*.o platformer
