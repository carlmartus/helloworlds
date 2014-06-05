PROGS=hello
FLAGS=-Wall -O2 -g -liup -lX11
FLAGS+= `pkg-config --libs gtk+-2.0`

all: $(PROGS)

%: %.c
	$(CC) -o $@ $< $(FLAGS)

clean:
	$(RM) $(PROGS)

