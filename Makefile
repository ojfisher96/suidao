CXX=g++
CXXFLAGS=-std=c++11 -g -p -pg -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wextra -Wno-unused-parameter -Wno-unused-function -iquote include/

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -I include/win
endif

all: suidao

ifeq ($(OS),Windows_NT)

release:
		@make clean
		make all CXXFLAGS='-std=c++11 -O2 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wextra -Werror -Wno-unused-parameter -Wno-unused-function -iquote include/ -I include/win'

else

release:
		@make clean
		make all CXXFLAGS='-std=c++11 -O2 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wextra -Werror -Wno-unused-parameter -Wno-unused-function -iquote include/'

endif

clean:
		rm -f src/*.o
	    rm -f suidao

suidao:        src/content.o src/game.o src/game_loop.o src/main.o src/map.o
		$(CXX) $(CXXFLAGS) -o suidao src/*.o -lSDL -lSDL_image -lSDL_mixer

src/%.o: src/%.cpp include/%.hpp


