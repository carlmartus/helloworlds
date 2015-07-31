PROGS=triangle point glsl_const
FLAGS=-std=gnu11 -Wall -O2 -g -lSDL -lGL -lGLEW

all: $(PROGS)

point: point.c glstuff.c
	$(CC) -o $@ $^ $(FLAGS)

triangle: triangle.c glstuff.c
	$(CC) -o $@ $^ $(FLAGS)

glsl_const: glsl_const.c glstuff.c
	$(CC) -o $@ $^ $(FLAGS)

clean:
	$(RM) $(PROGS)

