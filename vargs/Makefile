SRC=$(wildcard *.c)
PROGS=$(SRC:%.c=prog_%)

all: $(PROGS)

prog_%: %.c
	$(CC) -o $@ $< -Wall -O2 -std=gnu11

clean:
	$(RM) $(PROGS)

