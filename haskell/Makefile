SRC=$(wildcard *.hs)
DST=$(SRC:%.hs=%)

.PHONY: all clean

all: $(DST) ffi

%: %.hs
	ghc $<

ffi: ffi.hs ffi_c.c
	ghc -c ffi.hs -o ffi.o
	gcc -c ffi_c.c -o ffi_c.o
	ghc ffi.o ffi_c.o -o ffi

clean:
	$(RM) $(DST)

