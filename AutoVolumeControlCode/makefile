CPP = g++
CPPFLAG = std=c++11 -g -pedantic -Wall -Weffc++ -Wextra
DEBUG = -DNDEBUG -O3

main.o: main.o
	$(CPP) -I ./headers/. ./main/main.c ./c/main_functions.c ./c/user_functions.c -o ./out/main.o -lasound

debug.o: debug.o
	$(CPP) $(DEBUG) -I ./headers/. ./main/main_test.c ./c/tests.c ./c/main_functions.c ./c/user_functions.c -o ./out/debug.o -lasound

all: main.o debug.o

clean:
	$(RM) ./out/*.o ./out/debug.out ./out/main.out