CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -g
CXXFLAGS = -Wall -Wextra -g -std=c++17

ifeq ($(OS),Windows_NT)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET = sim.exe
    TEST_TARGET = test.exe
else
    LIBS = -lraylib -lm
    TARGET = sim
    TEST_TARGET = test
endif

all: $(TARGET)

$(TARGET): main.cpp sim.cpp physics.o renderer.o
	$(CXX) $(CXXFLAGS) main.cpp sim.cpp physics.o renderer.o -o $(TARGET) $(LIBS)

physics.o: physics.c physics.h
	$(CC) $(CFLAGS) -c physics.c -o physics.o

renderer.o: renderer.c renderer.h
	$(CC) $(CFLAGS) -c renderer.c -o renderer.o

test: test.c physics.o
	$(CC) $(CFLAGS) test.c physics.o -o $(TEST_TARGET) -lm

clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)