#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DELIM " \n\t[]"

int main(int argc, char *argv[]) {
	char *token;
	char *string;
       
	string = (char *) malloc(300);
	strcpy(string, "table iris\n\tid int order\n\tpl double\n\tpw double\n\tsl double\n\tsw double\n\tclass char[50]\n");

	token = strtok(string, DELIM); printf("Token = %s\n", token);

	while ((token = strtok(NULL, DELIM)) != NULL) {
	       	printf("Token = %s\n", token);
	}

	printf ("%s", string);

	return 0;
}
