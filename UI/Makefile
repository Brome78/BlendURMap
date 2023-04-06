# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0 sdl2 SDL2_image` -lm -g -O1
LDLIBS = `pkg-config --libs gtk+-3.0 sdl2 SDL2_image` -lm -g

SRC= $(wildcard *.c) $(wildcard */*.c) $(wildcard ../Generation/*/*.c)

OBJ = ${SRC:.c=.o}

EXE = ui

all: $(EXE)

${EXE}: ${SRC}

.PHONY: clean

clean:
	${RM} $(EXE)

# END
