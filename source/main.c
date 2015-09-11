#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define	DELIMITER " \n\t[]"
#define BUFFER_SIZE 1024

/*	Field FIELD
 *
 *	Estrutura que guarda o nome, tamanho e tipo de um campo.
 *	- Membros:
 *		char *: nome do campo;
 *		char *: tipo do campo;
 *		int: tamanho do campo;
 *		char: booleano que indica se o campo é ou não de índice.
 */
typedef struct Field FIELD;

/*	Schema SCHEMA
 *
 *	Estrutura que descreve como é cada dado.
 *	- Membros:
 *		int: tamanho de cada dado;
 *		int: número de campos que cada dado;
 *		char *: nome do registro de cada dado;
 *		FIELD *: vetor com os campos do registro.
 */
typedef struct Schema SCHEMA;

/*	readUntilChar ()
 *
 *	Função para ler um string até determinado caractere.
 *	- Parâmetros:
 *		FILE *: arquivo do qual a string deve ser lida;
 *		const char: caractere terminador.
 *	- Retorno:
 *		char *: cadeia de caracteres lida.
 */
char * readUntilChar (FILE *, const char);

/*	getSchema ()
 *
 *	Função para ler e armazenar o conteúdo do .schema.
 *	- Parâmetros:
 *		const char *: nome do arquivo .schema.
 *	- Retorno:
 *		SCHEMA *: endereço da estrutura com as informações sobre o registro descrito no .schema.
 */
SCHEMA * getSchema (const char *);

/*	dumpSchema ()
 *
 *	Função para imprimir a descrição do arquivo de dados baseado no schema fornecido.
 *	- Parâmetros:
 *		SCHEMA *: endereço da estrutura que contém as informações retiradas do .schema.
 *	- Retorno:
 *		não há.
 */
void dumpSchema (SCHEMA * schema);

/*	freeSchema ()
 *
 *	Função para liberar a estrutura com a descrição dos registros completamente.
 *	- Parâmetros:
 *		SCHEMA *: endereço da estrutura que será liberada.
 *	- Retorno:
 *		não há.
 */
void freeSchema (SCHEMA *);

void * readData (SCHEMA *, int *);

void fprintInt (void *, int, FILE *);

void fprintDouble (void *, int, FILE *);

void fprintString (void *, int, FILE *);

void fwriteInt (void *, int, FILE *);

void fwriteDouble (void *, int, FILE *);

void fwriteString (void *, int, FILE *, int);

int getInternOffset (SCHEMA *, int);

void createIndex (void *, SCHEMA *, int);

int main (int argc, char * argv[]) {
	char * schemaName;
	SCHEMA * schema;
	void * data;
	int recordsNumber;

	schemaName = readUntilChar (stdin, '\n');
	schema = getSchema (schemaName);

	data = readData (schema, &recordsNumber);

	createIndex (data, schema, recordsNumber);

	freeSchema (schema);
	free (data);
	free (schemaName);

	return 0;
}

typedef struct Field {
	char * name;
	char * type;
	int size;
	char order;
} FIELD;


typedef struct Schema {
	int size;
	int fieldsNumber;
	char * table;
	FIELD * fields;
} SCHEMA;

char * readUntilChar (FILE * p_file, const char delimiter) {
	char read;
	char * string = NULL;
	int i;

	for (i = 0; !feof (p_file) && (read = fgetc (p_file)) != delimiter; i++) {
		if (i % BUFFER_SIZE == 0)
			string = (char *) realloc (string, (i + BUFFER_SIZE) * sizeof (char));

		string[i] = read;
	}

	string = (char *) realloc (string, (i + 1) * sizeof (char));
	string[i] = '\0';

	return string;
}

SCHEMA * getSchema (const char * schemaName) {
	FILE * p_schema = NULL;
	SCHEMA * schema = NULL;
	int schemaSize, i;
	char * schemaContent;
	char * token = NULL;

	p_schema = fopen (schemaName, "r");

	fseek (p_schema, 0, SEEK_END);
	schemaSize = ftell (p_schema);

	schemaContent = (char *) malloc ((schemaSize + 1) * sizeof (char));

	fseek (p_schema, 0, SEEK_SET);
	for (i = 0; i < schemaSize; i++) {
		schemaContent[i] = fgetc (p_schema);
	}
	schemaContent[i] = '\0';

	schema = (SCHEMA *) malloc (sizeof (SCHEMA));
	schema->fields = NULL;
	schema->table = NULL;
	schema->size = 0;

	token = strtok (schemaContent, DELIMITER);
	token = strtok (NULL, DELIMITER);

	schema->table = (char *) malloc ((strlen (token) + 1) * sizeof (char));
	strcpy (schema->table, token);

	token = strtok (NULL, DELIMITER);

	for (i = 0; token != NULL; i++) {
		schema->fields = (FIELD *) realloc (schema->fields, (i + 1) * sizeof (FIELD));

		schema->fields[i].name = (char *) malloc ((strlen (token) + 1) * sizeof (char));
		strcpy (schema->fields[i].name, token);

		token = strtok (NULL, DELIMITER);
		schema->fields[i].type = (char *) malloc ((strlen (token) + 1) * sizeof (char));
		strcpy (schema->fields[i].type, token);

		if (strcmp (token, "char") == 0) {
			token = strtok (NULL, DELIMITER);
			schema->fields[i].size = (int) strtol (token, NULL, 10);
		}
		else {
			if (strcmp (schema->fields[i].type, "int") == 0) schema->fields[i].size = sizeof (int);
			else schema->fields[i].size = sizeof (double);
		}
		schema->size += schema->fields[i].size;

		token = strtok (NULL, DELIMITER);
		if (token != NULL && strcmp (token, "order") == 0) {
			schema->fields[i].order = 1;
			token = strtok (NULL, DELIMITER);
		}
		else {
			schema->fields[i].order = 0;
		}
	}

	schema->fieldsNumber = i;

	free (token);
	fclose (p_schema);
	free (schemaContent);

	return schema;
}

void dumpSchema (SCHEMA * schema) {
	int i;

	printf ("table %s(%d bytes)\n", schema->table, schema->size);

	for (i = 0; i < schema->fieldsNumber; i++) {
		printf ("%s %s", schema->fields[i].name, schema->fields[i].type);
		if (schema->fields[i].order == 1) printf (" order");
		printf ("(%d bytes)\n", schema->fields[i].size);
	}
}

void freeSchema (SCHEMA * schema) {
	int i;

	for (i = 0; i < schema->fieldsNumber; i++) {
		free (schema->fields[i].name);
		free (schema->fields[i].type);
	}
	free (schema->fields);
	free (schema->table);
	free (schema);
}

void * readData (SCHEMA * schema, int * recordsNumber) {
	void * data = NULL;
	FILE * p_data = NULL;
	char * filename = NULL;

	filename = (char *) malloc ((strlen(schema->table) + strlen(".data") + 1) * sizeof (char));
	strcpy (filename, schema->table);
	strcpy (filename + strlen (schema->table), ".data");
	filename[(int) strlen (schema->table) + strlen (".data")] = '\0';

	p_data = fopen (filename, "r");

	fseek (p_data, 0, SEEK_END);
	*recordsNumber = (ftell (p_data) / schema->size);
	fseek (p_data, 0, SEEK_SET);

	data = malloc (*recordsNumber * schema->size);
	fread (data, schema->size, *recordsNumber, p_data);

	free (filename);
	fclose (p_data);

	return data;
}

void fprintInt (void * data, int offset, FILE * output) {
	char * transition;
	int * number;

	transition = (char *) data;
	transition += offset;

	number = (int *)transition;

	fprintf (output, "%d", *number);
}

void fprintDouble (void * data, int offset, FILE * output) {
	char * transition;
	double * number;

	transition = (char *) data;
	transition += offset;

	number = (double *) transition;

	fprintf (output, "%lf", *number);
}

void fprintString (void * data, int offset, FILE * output) {
	char * string;

	string = (char *) data;
	string += offset;

	fprintf (output, "%s", string);
}

void fwriteInt (void * data, int offset, FILE * output) {
	char * transition;

	transition = (char *) data;
	transition += offset;

	fwrite ((void *) transition, sizeof(int), 1, output);
}

void fwriteDouble (void * data, int offset, FILE * output) {
	char * transition;

	transition = (char *) data;
	transition += offset;

	fwrite ((void *) transition, sizeof(double), 1, output);
}

void fwriteString (void * data, int offset, FILE * output, int size) {
	char * transition;

	transition = (char *) data;
	transition += offset;

	fwrite ((void *) transition, size, 1, output);
}

int getInternOffset (SCHEMA * schema, int position) {
	int offset, i;

	for (offset = 0, i =0; i < position; i++) {
		 offset += schema->fields[i].size;
	}

	return offset;
}

/* TODO criar uma função para criar o nome. */
void createIndex (void * data, SCHEMA * schema, int recordsNumber) {
	int i, j, internOffset;
	int tableNameSize, fieldNameSize, extensionSize;
	char * filename;
	FILE * idx;

	for (i = 0; i < schema->fieldsNumber; i++) {
		internOffset = getInternOffset (schema, i);
		printf ("%s intern offset = %d\n", schema->fields[i].name, internOffset);

		if (schema->fields[i].order) {
			tableNameSize = strlen (schema->table);
			fieldNameSize = strlen (schema->fields[i].name);
			extensionSize = strlen (".idx");

			filename = (char *) malloc ((tableNameSize + 1 + fieldNameSize + extensionSize + 1) * sizeof (char));
			strcpy (filename, schema->table);
			strcat (filename, "-");
			strcat (filename, schema->fields[i].name);
			strcat (filename, ".idx");

			idx = fopen (filename, "w+");
			internOffset = getInternOffset (schema, i);

			for (j = 0; j < recordsNumber * schema->size; j += schema->size) {
				fwrite ((void *) &j, sizeof (int), 1, idx);
				if (strcmp (schema->fields[i].type, "int") == 0) 
					fwriteInt (data, j + internOffset, idx);
				else if (strcmp (schema->fields[i].type, "double") == 0)
					fwriteDouble (data, j + internOffset, idx);
				else 
					fwriteString (data, j + internOffset, idx, schema->fields[i].size);
			}

			free (filename);
			fclose (idx);
		}
	}
}
