#include <stdio.h>
#include <string.h>

int
main()
{
	printf("Seperating using strsep\n");

	char csv[] = "Name;Title;Misc";
	const char *delimiter = ";"; // Can be const

	char *aux = csv;
	char *word = strsep(&aux, delimiter);
	while (word) {
		printf("Word (%s)\n", word);
		word = strsep(&aux, delimiter);
	}

	return 0;
}

