CPP=g++
CPPFLAGS=-std=c++11 -Wall -Wextra -I libtcod-mac/include -I /usr/local/include/SDL
LIBS=
EXE=run_roguelike

OBJ_DIR=obj
SRC_DIR=src

_DEPS=
DEPS=$(patsubst %,$(SRC_DIR)/%,$(_DEPS))

_OBJ=main.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

OS := $(shell uname)

ifeq ($(OS),Darwin)
# Mac OS
	LIBS+=-L libtcod-mac -lSDL -ltcod -ltcodxx
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
	@cd libtcod-mac; make -f makefiles/makefile-osx release
	@cp -p libtcod-mac/libtcod.dylib .
	@cp -p libtcod-mac/libtcodxx.dylib .
	@cp -p libtcod-mac/terminal.png .
	@mkdir -p $(OBJ_DIR)

.PHONY: clean

clean:
	@echo "Cleaning"
	@rm -f $(OBJ_DIR)/*.o *~ $(SRC_DIR)/*~
	@rm -f libtcod* terminal.png
