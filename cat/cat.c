/* cat.c: print contents of file supplied by arguement to stdout */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* die: exit the program with an optional error message and specified return value */
void die(const char *msg, int ret) {
	if (msg != NULL) {
		perror(msg);
	}
	exit(ret);
}

/* extract: return a char * array which contains all the lines of filename */
char **extract(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		die("unable to open file", -1);
	}
	
	char **content = NULL;
	char *line = NULL;
	ssize_t linelen;
	size_t  linecap = 0;
	int i = 0;
	
	while ((linelen = getline(&line, &linecap, fp)) != -1) {
		content = realloc(content, sizeof(char*)*(i+1));
		content[i] = malloc(sizeof(char)*(linelen+1));
		strcpy(content[i++], line);
	}
	content = realloc(content, sizeof(char*)*(i+1));
	content[i] = NULL;
	
	free(line);
	fclose(fp);
	return content;
}

int main(int argc, char **argv)
{
	char **output = NULL;
	if (argc < 2) {
		printf("no file argument supplied!\n");
		exit(EXIT_SUCCESS);
	}
	
	for (int i = 1; i < argc; i++) {
		output = extract(argv[i]);
		for (int j = 0; output[j]; j++) {
			printf("%s", output[j]);
		}
		free(output);
	}
	
	exit(EXIT_SUCCESS);
}
