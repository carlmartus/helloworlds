APPS=client server
CFLAGS=-Wall -O2
LDFLAGS=-lenet

all: $(APPS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(APPS)

