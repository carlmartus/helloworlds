#include <stdio.h>
#include <stdarg.h>

typedef enum {
	LOG_INFO,
	LOG_WARN,
	LOG_ERRO,
} LogCode;

static void
log_msg(LogCode code, const char *fmt, ...)
{
	const char *prefix = NULL;
	switch (code) {
		case LOG_INFO : prefix = "\033[92minfo"; break;
		case LOG_WARN : prefix = "\033[93mwarn"; break;
		default :
		case LOG_ERRO : prefix = "\033[91merro"; break;
	}

	printf(" (%s\033[0m) : ", prefix);

	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	putchar('\n');
}

int
main(int argc, char **argv)
{
	log_msg(LOG_INFO, "Starting program");
	log_msg(LOG_ERRO, "Only using %d parameters", argc);
	log_msg(LOG_WARN, "This is your warning!");
	log_msg(LOG_INFO, "Let's print some arguments: %.2x %d (%s)",
			2, 3, "Hello!");
	return 0;
}

