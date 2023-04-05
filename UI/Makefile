# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 sdl2 SDL2_image` -lm -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0 sdl2 SDL2_image` -lm

SRC= $(wildcard *.c)

OBJ = ${SRC:.c=.o}

EXE = ui

all: $(EXE)

${EXE}: ${SRC}

.PHONY: clean

clean:
	${RM} $(EXE)

# END
