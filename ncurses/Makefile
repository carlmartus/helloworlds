SRC=$(wildcard *.c)
PROG=$(SRC:%.c=%)
CFLAGS=-std=gnu99

.PHONY: all clean

all: $(PROG)

rtlog: rtlog.c
	$(CC) $(CFLAGS) -o $@ $< -lncurses -lpthread

%: %.c
	$(CC) $(CFLAGS) -o $@ $< -lncurses

clean:
	$(RM) $(PROG)

