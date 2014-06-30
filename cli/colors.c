#include <stdio.h>

#define COL_BASE "\033[0m"
#define COL_SUCC "\033[92m"
#define COL_WARN "\033[93m"
#define COL_ERRO "\033[91m"

int
main()
{
	printf(
			COL_BASE "Hello!, This is " 
			COL_SUCC "ok" COL_BASE ", "
			COL_WARN "warning" COL_BASE ", "
			COL_ERRO "error" COL_BASE "...\n");
	return 0;
}

