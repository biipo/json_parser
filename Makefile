OPTIONS=-O3 -DNDEBUG -Wall -Wextra

all:test

sanitiezers: OPTIONS=-fsanitize=address and -fno-omit-frame-pointer -g -DDEBUG -Wall -Wextra
sanitiezers:test

debug: OPTIONS=-O0 -g -DDEBUG -Wall -Wextra
debug:test

test: json.o main.cpp
	g++ ${OPTIONS} main.cpp -o test

json.o:	json.cpp json.hpp
	g++ ${OPTIONS} -c json.cpp -o json.o 

clean:
	rm -rf *.o test out.json
