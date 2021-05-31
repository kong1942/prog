#include "sort.h"

int main(int argc, char **argv)
{
	int i=0, j=0, k=0;
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
		int tmp;
		for(i=1; i<DATANUM; i++)
		{
			for(j=0; j<i; j++)
			{
				if(arrOfNum[i] < arrOfNum[j])
				{
					tmp = arrOfNum[i];
					for(k=i; k>j; k--)
						arrOfNum[k] = arrOfNum[k-1];
					arrOfNum[j] = tmp;
				}
			}
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
		char tmp[MAXLEN];
		for(i=1; i<DATANUM; i++)
		{
			for(j=0; j<i; j++)
			{
				if(strcmp(arrOfStr[i], arrOfStr[j]) < 0)
				{
					strcpy(tmp, arrOfStr[i]);
					for(k=i; k>j; k--)
						strcpy(arrOfStr[k], arrOfStr[k-1]);
					strcpy(arrOfStr[j], tmp);
				}
			}
		}
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
