PROGS=triangle
FLAGS=-std=gnu11 -Wall -O2 -g -lSDL -lGL -lGLEW

all: $(PROGS)

triangle: triangle.c glstuff.c
	$(CC) -o $@ $^ $(FLAGS)

clean:
	$(RM) $(PROGS)

