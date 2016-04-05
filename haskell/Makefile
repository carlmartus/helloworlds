all: ffi

ffi: ffi.hs ffi_c.c
	ghc -c ffi.hs -o ffi.o
	gcc -c ffi_c.c -o ffi_c.o
	ghc ffi.o ffi_c.o -o ffi

