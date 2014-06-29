/**
 * WARNING strtok is not thread safe!!!!!
 * use strtok_r instead.
 */

#include <stdio.h>
#include <string.h>

int
main()
{
	char csv[] = "Name;Title;Misc";
	char delimiter[] = ";";

	char *word = strtok(csv, delimiter);
	while (word) {
		printf("Word (%s)\n", word);
		word = strtok(NULL, delimiter);
	}
	return 0;
}

