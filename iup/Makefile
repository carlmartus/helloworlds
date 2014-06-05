PROGS=hello
FLAGS=-Wall -O2 -g -liup -lX11 -lm 
FLAGS+= -lgtk-x11-2.0 -lgdk-x11-2.0 -lgtk-3 -lgdk-3 -lgdk_pixbuf-2.0 -lpango-1.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0

all: $(PROGS)

%: %.c
	$(CC) -o $@ $< $(FLAGS)

clean:
	$(RM) $(PROGS)

