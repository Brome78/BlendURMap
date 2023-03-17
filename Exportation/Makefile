# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra `pkg-config --cflags sdl2 SDL2_image` -lm -g
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

SRC=

OBJ = ${SRC:.c=.o}
EXE = export

all: ${EXE}

${EXE}: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ} ${EXE} *.obj
