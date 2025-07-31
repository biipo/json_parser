CXX = g++
CXXFLAGS = -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -I include/

PROD = -O3

ASAN_FLAGS = -fsanitize=address -O1 -fno-omit-frame-pointer -Wno-format-security

DEBUG = -O0 -g -DDEBUG -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -pedantic-errors -I include/

all: main

main: src/main.cpp json
	$(CXX) $(CXXFLAGS) src/main.cpp build/json.o -o build/main 

sanitize: src/json.cpp include/json.hpp
	$(CXX) $(DEBUG) $(ASAN_FLAGS) -c src/json.cpp -o build/json.o

debug: src/json.cpp include/json.hpp
	$(CXX) $(DEBUG) -c src/json.cpp -o build/json.o

json: src/json.cpp include/json.hpp
	$(CXX) $(CXXFLAGS) -c src/json.cpp -o build/json.o 

clean:
	rm -rf build/*
