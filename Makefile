CC              = gcc
CFLAGS          = -I $(INC_DIR) -I $(SDL_INC_DIR) -g
LIBS            = -lSDL2

SDL_INC_DIR     = /usr/include/SDL2

INC_DIR		= include
SRC_DIR         = src
OBJ_DIR         = obj

PREFIX          = /usr/local
APPLICATIONS    = /usr/share/applications

_DEPS           = evosim.h
DEPS            = $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJ            = main.o list.o reproduction.o movement.o life_cycle.o graphics.o
OBJ             = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: evosim clean

evosim: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o

.PHONY: clean
