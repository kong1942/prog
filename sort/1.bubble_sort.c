#include "sort.h"

int main(int argc, char **argv)
{
	int i=0, j=0;
	int len;
	char line[MAXLEN];
	FILE *fp;
       	if(fp = fopen("data", "r") == NULL)
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
			for(j=0; j<DATANUM-i-1; j++)
				if(arrOfNum[j] > arrOfNum[j+1]) swap(&arrOfNum[j], &arrOfNum[j+1], 'n');
		for(i=0; i<DATANUM; i++)		
			printf("%d\n", arrOfNum[i]);
		free(arrOfNum);
	}
	else if(argc == 2 && !strcmp(argv[1], "-s"))
	{
		char **arrOfStr = (char **)malloc(sizeof(char *) * DATANUM);
		i=0;
		while(fgets(line, MAXLEN, fp))
		{
			len = strlen(line);
			if(line[len-1] == '\n') line[len-1] = '\0';
			arrOfStr[i] = strdup(line);
			i++;
		}
		for(i=0; i<DATANUM-1; i++)
			for(j=0; j<DATANUM-i-1; j++)
				if(strcmp(arrOfStr[j], arrOfStr[j+1]) > 0) swap(&arrOfStr[j], &arrOfStr[j+1], 's');
		for(i=0; i<DATANUM; i++)		
		{
			printf("%s\n", arrOfStr[i]);
			free(arrOfStr[i]);
		}
		free(arrOfStr);
	}
	else errmsg("error");
	
	fclose(fp);

	return 0;
}
