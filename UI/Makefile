# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 sdl2 SDL2_image` -lm -g -O1
LDLIBS = `pkg-config --libs gtk+-3.0 sdl2 SDL2_image` -lm -g

SRC= $(wildcard *.c) $(wildcard */*.c) $(wildcard ../Generation/*/*.c)

OBJ = ${SRC:.c=.o}

EXE = BlendURMap

all: $(EXE)

${EXE}: ${SRC}

.PHONY: clean

clean:
	${RM} $(EXE) tmp/river.png tmp/village.png tmp/map_forest.png tmp/chunk.png\
	 *.OBJ *~

# END
