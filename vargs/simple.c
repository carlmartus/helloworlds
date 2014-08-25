#include <stdio.h>
#include <stdarg.h>

enum types {
	TYPE_INT,
	TYPE_DOUBLE,
};

static void
inspect(int count, ...)
{
	va_list args;

	va_start(args, count);

	int data_int;
	double data_float;

	int i;
	for (i=0; i<count; i++) {
		int type = va_arg(args, int);

		switch (type) {
			default :
			case TYPE_INT :
				data_int = va_arg(args, int);
				printf("Got int: %d\n", data_int);
				break;

			case TYPE_DOUBLE :
				data_float = va_arg(args, double);
				printf("Got float: %f\n", data_float);
				break;
		}
	}

	va_end(args);
}

int
main(int argc, char **argv)
{
	inspect(2, TYPE_INT, 3, TYPE_DOUBLE, 1.234567);

	inspect(5,
			TYPE_INT, 1,
			TYPE_INT, 2,
			TYPE_INT, 3,
			TYPE_INT, 4,
			TYPE_INT, 5);
	return 0;
}

