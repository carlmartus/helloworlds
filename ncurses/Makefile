SRC=$(wildcard *.c)
PROG=$(SRC:%.c=%)

all: $(PROG)

%: %.c
	$(CC) -o $@ $< -lncurses

clean:
	$(RM) $(PROG)

