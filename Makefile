CPP=g++
CPPFLAGS=-std=c++11 -Wall -Wextra -I libtcod/src -I /usr/local/include/SDL
LIBS=
EXE=run_roguelike

OBJ_DIR=obj
SRC_DIR=src

_DEPS=actor.hpp ai.hpp attacker.hpp bsplistener.hpp destructible.hpp engine.hpp gui.hpp map.hpp
DEPS=$(patsubst %,$(SRC_DIR)/%,$(_DEPS))

_OBJ=actor.o ai.o attacker.o bsplistener.o destructible.o engine.o gui.o main.o map.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

OS := $(shell uname)

ifeq ($(OS),Darwin)
# Mac OS
	LIBS+=-L libtcod -lSDL -ltcod -Wl,-rpath .
else
# Assume Linux for now
	LIBS+=-lSDL
endif

default: debug

debug: CPPFLAGS += -g
debug: build

release: CPPFLAGS += -O2
release: build

build: setup_build $(EXE)
	@echo "Build finished"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CPP) $(CPPFLAGS) -c -o $@ $<

$(EXE): $(OBJ)
	$(CPP) $(CPPFLAGS) $(LIBS) $^ -o $@

setup_build:
	@cd libtcod/build/autotools ; autoreconf -i ; ./configure CFLAGS='-O2' --prefix=$(PWD)/libtcod/; make -j 4; make install
	@cp -pL libtcod/lib/libtcod.dylib .
	@cp -p libtcod/terminal.png .
	@mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	@echo "Cleaning"
	@rm -f $(OBJ_DIR)/*.o *~ $(SRC_DIR)/*~
	@rm -f libtcod.* terminal.png
	@cd libtcod/build/autotools ; make clean
	@rm run_roguelike

