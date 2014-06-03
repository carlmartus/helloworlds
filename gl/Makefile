PROGS=triangle
FLAGS=-Wall -O2 -lSDL -lGL -lGLEW

all: $(PROGS)

%: %.c
	$(CC) -o $@ $< $(FLAGS)

clean:
	$(RM) $(PROGS)

