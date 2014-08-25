#include <stdio.h>
#include <string.h>

int
main()
{
	printf("Seperating using strtok_r\n");

	char csv[] = "Name;Title;Misc";
	char delimiter[] = ";";

	char *aux;

	char *word = strtok_r(csv, delimiter, &aux);
	while (word) {
		printf("Word (%s)\n", word);
		word = strtok_r(NULL, delimiter, &aux);
	}

	return 0;
}


