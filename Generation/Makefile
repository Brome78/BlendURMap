# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra `pkg-config --cflags sdl2 SDL2_image` -lm -g
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

SRC = Utils/utils.c Noise/perlin.c Noise/simplex.c Noise/diamond_square.c \
		Color/chunk.c Color/color.c Color/props.c Color/biome.c Noise/seed.c main.c
OBJ = ${SRC:.c=.o}
EXE = main

all: ${EXE}

${EXE}: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ} ${EXE} *.png *.bmp
