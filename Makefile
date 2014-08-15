CXX=g++
CXXFLAGS=-std=c++11 -g -p -pg -pedantic -Wall -Wpointer-arith -Wcast-qual -Wextra -Wno-unused-parameter -Wno-unused-function -iquote include/


ifeq ($(OS),Windows_NT)
	CXXFLAGS += -I include/win -I ../SDL/include
	LDFLAGS= -L ../SDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -mwindows
else
	LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -ljsoncpp -lSDL2_ttf -llua5.2
endif

all: suidao

ifeq ($(OS),Windows_NT)

release:
		@make clean
		make all CXXFLAGS='-std=c++11 -O2 -pedantic -Wall -Wpointer-arith -Wcast-qual -Wextra -Werror -Wno-unused-parameter -Wno-unused-function -iquote include/ -I include/win'

else

release:
		@make clean
		make all CXXFLAGS='-std=c++11 -O2 -pedantic -Wall -Wpointer-arith -Wcast-qual -Wextra -Werror -Wno-unused-parameter -Wno-unused-function -iquote include/'

endif

clean:
		rm -f src/*.o
	    rm -f suidao

suidao:        src/content.o src/game.o src/game_loop.o src/main.o src/map.o src/game_state.o src/animation.o src/unit.o src/lua_api.o src/menu.o
	$(CXX) $(CXXFLAGS) -o suidao src/*.o $(LDFLAGS)

src/%.o: src/%.cpp include/%.hpp
