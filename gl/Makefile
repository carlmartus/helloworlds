PROGS=triangle point glsl_const stencil
FLAGS=-std=gnu11 -Wall -O2 -g -lSDL -lGL -lGLEW -lm

all: $(PROGS)

%: %.c glstuff.c glstuff.h
	$(CC) -o $@ $< glstuff.c $(FLAGS)

clean:
	$(RM) $(PROGS)

