#include <stdlib.h>
#include <stdio.h>

int main (int argc, char * argv[]) {
	int * cheio = NULL;
	int quantidade;

	scanf("%d", &quantidade);

	cheio = (int *) malloc (quantidade * sizeof (int));

	if (cheio) {
		printf("Alocou alguma coisa!\n");
		free(cheio);
	} else {
		printf("Não alocou nada.\n");
	}

	return 0;
}
