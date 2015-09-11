#include <stdlib.h>
#include <stdio.h>

int main (int argc, char * argv[]) {
	FILE * pfile;
	char string[20];

	pfile = fopen ("teste.txt", "w+");

	fprintf (pfile, "%s", "ERA UMA VEZ UMA GATO XADREZ");

	fseek (pfile, 0, SEEK_END);
	printf ("%d\n", ftell (pfile));
	fseek (pfile, 0, SEEK_SET);

	fscanf (pfile, "%s", &string);

	printf ("%s\n", string);

	fclose (pfile);

	return EXIT_SUCCESS;
}
