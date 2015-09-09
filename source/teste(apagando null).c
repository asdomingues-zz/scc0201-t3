/*	Liberando memórias não alocadas e alocando nada na memória
 *
 *	Programa para testar qual o comportamento do sistema
 *	ao alocar memória de tamanho 0 ou liberar um ponteiro
 *	nulo.
 *
 *	Allan S. Domingues | 9293290 | ICMC-USP | 29/08/15
 */

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
		cheio = NULL;
	} else {
		printf("Não alocou nada.\n");
	}

	if (cheio == NULL) {
		fprintf(stderr, "O free de um ponteiro para NULL será feito a seguir!\n");
		free(cheio);
	}

	return 0;
}
