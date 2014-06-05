PROGS=hello
FLAGS=-Wall -O2 -g -liup -lX11
FLAGS+= `pkg-config --libs gtk+-2.0`

MINGW32=mingw32gcc
MINGW_IUP_LD=/opt/mingw32/lib/libiup.a
MINGW_IUP_HEADERS=/opt/mingw32/include
MINGW_FLAGS=-lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -Wl,-subsystem,windows

all: $(PROGS)

win: $(PROGS:%=%.exe)

%: %.c
	$(CC) -o $@ $< $(FLAGS)

%.exe: %.c
	$(MINGW32) -o $@ $< $(MINGW_IUP_LD) $(MINGW_FLAGS) -I"$(MINGW_IUP_HEADERS)"

win:

clean:
	$(RM) $(PROGS)

