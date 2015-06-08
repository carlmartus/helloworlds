SRC=$(wildcard *.c)
PROG=$(SRC:%.c=%)

.PHONY: all clean

all: $(PROG)

rtlog: rtlog.c
	$(CC) -o $@ $< -lncurses -lpthread

%: %.c
	$(CC) -o $@ $< -lncurses

clean:
	$(RM) $(PROG)

