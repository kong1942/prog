#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 1024
#define DATANUM 1e4
#define TRUE 1
#define FALSE 0

void errmsg(char *str)
{
	fprintf(stderr, "%s\n", str);
}

void getcommand(char *line, char *command)
{
	char *ptr = line;
	char *qtr = command;
	while(qtr - command < 5 && isalpha(*ptr)) {*qtr++ = *ptr++;}
	*qtr = '\0';
}

void rmNewline(char *line)
{
	int len = strlen(line);
	if(line[len-1] == '\n') line[len-1] = '\0';
}
