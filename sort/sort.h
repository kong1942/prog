#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXLEN 15
#define DATANUM 1e4

void errmsg(char *str)
{
	fprintf(stderr, "%s\n", str);
}

void swap(void *a, void *b, char mode)
{
	if(mode == 'n')
	{
		int tmp = *(int *)a;
		*(int *)a = *(int *)b;
		*(int *)b = tmp;
	}
	else if(mode == 's')
	{
		char tmp[MAXLEN];
		strcpy(tmp, *(char **)a);
		strcpy(*(char **)a, *(char **)b);
		strcpy(*(char **)b, tmp);
	}
	else return;
}
