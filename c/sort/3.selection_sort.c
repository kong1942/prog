#include "sort.h"

int main(int argc, char **argv)
{
	int i=0, j=0, min;
	char line[MAXLEN];
	FILE *fp;
       	if((fp = fopen("data", "r")) == NULL)
		errmsg("data error");
	
	if(argc == 1 || !strcmp(argv[1], "-n"))
	{
		int *arrOfNum = (int *)malloc(sizeof(int) * DATANUM);
		while(fgets(line, MAXLEN, fp))
		{
			arrOfNum[i] = atoi(line);
			i++;
		}
		for(i=0; i<DATANUM-1; i++)
		{
			min = i;
			for(j=i+1; j<DATANUM; j++)
				if(arrOfNum[j] < arrOfNum[min])
					min = j;
			swap(&arrOfNum[i], &arrOfNum[min], 'n');
		}
		for(i=0; i<DATANUM; i++)
			printf("%d\n", arrOfNum[i]);
		free(arrOfNum);
	}
	else if(argc == 2 && !strcmp(argv[1], "-s"))
	{
		int len;
		char **arrOfStr = (char **)malloc(sizeof(char *) * DATANUM);
		while(fgets(line, MAXLEN, fp))
		{
			len = strlen(line);
			if(line[len-1] == '\n') line[len-1] = '\0';
			arrOfStr[i] = strdup(line);
			i++;
		}
		for(i=0; i<DATANUM-1; i++)
		{
			min = i;
			for(j=i+1; j<DATANUM; j++)
				if(strcmp(arrOfStr[j], arrOfStr[min]) < 0)
					min = j;
			swap(&arrOfStr[i], &arrOfStr[min], 's');
		}
		for(i=0; i<DATANUM; i++)
		{
			printf("%s\n", arrOfStr[i]);
			free(arrOfStr[i]);
		}
		free(arrOfStr);
	}
	
	return 0;
}
