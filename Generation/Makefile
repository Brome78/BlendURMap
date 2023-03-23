# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra `pkg-config --cflags sdl2 SDL2_image` -lm -g
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

SRC= 	$(wildcard *.c) $(wildcard */*.c)

OBJ = ${SRC:.c=.o}
EXE = main

all: ${EXE}

${EXE}: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ} ${EXE} *.png *.bmp *.OBJ
