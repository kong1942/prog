//Use counting sort to sort each digit
//Least significant digit
#include "sort.h"
#define MAXDIGIT 11

void countingsort(char **arr, char **arr2, int digit);

int main(int argc, char **argv)
{
	int i=0, j=0, k=0;
	char line[MAXLEN];
	char **arr2 = (char **)malloc(sizeof(char *) * DATANUM);
	for(i=0; i<DATANUM; i++)
		arr2[i] = (char *)malloc(sizeof(char) * MAXLEN-1);
	FILE *fp;
       	if(fp = fopen("data", "r") == NULL)
		errmsg("data error");
	
	if(argc == 1 || !strcmp(argv[1], "-n"))
	{
		int len;
		char **arrOfNum = (char **)malloc(sizeof(char *) * DATANUM);
		for(i=0; i<DATANUM; i++)
			arrOfNum[i] = (char *)malloc(sizeof(char) * MAXLEN-1);
		while(fgets(line, MAXLEN, fp))
		{
			len = strlen(line);
			if(line[len-1] == '\n') {line[len-1] = '\0'; len--;}
			i=0;
			while(i != MAXLEN - 1 - len - 1)
			{
				arrOfNum[k][i] = '\0';
				i++;
			}
			j=0;
			while(i != MAXLEN - 1)
			{
				arrOfNum[k][i] = line[j];
				i++; j++;
			}
			k++;
		}
		for(i=MAXLEN-3; i>=0; i--)
			countingsort(arrOfNum, arr2, i);					//any stable sorting algorithm
		for(i=0; i<DATANUM; i++)
		{
			j=0;
			while(arrOfNum[i][j] == '\0') {j++;}
			printf("%s\n", &arrOfNum[i][j]);
			free(arrOfNum[i]);
			free(arr2[i]);
		}
		free(arrOfNum);
		free(arr2);
	}
	else if(argc == 2 || !strcmp(argv[1], "-s"))
	{
		
		int len;
		char **arrOfStr = (char **)malloc(sizeof(char *) * DATANUM);
		for(i=0; i<DATANUM; i++)
			arrOfStr[i] = (char *)malloc(sizeof(char) * MAXLEN-1);
		while(fgets(line, MAXLEN, fp))
		{
			len = strlen(line);
			if(line[len-1] == '\n') {line[len-1] = '\0'; len--;}
			i=0;
			while(i != len)
			{
				arrOfStr[k][i] = line[i];
				i++; j++;
			}
			while(i != MAXLEN - 1)
			{
				arrOfStr[k][i] = '\0';
				i++;
			}
			k++;
		}
		for(i=MAXLEN-3; i>=0; i--)
			countingsort(arrOfStr, arr2, i);
		for(i=0; i<DATANUM; i++)
		{
			printf("%s\n", arrOfStr[i]);
			free(arrOfStr[i]);
			free(arr2[i]);
		}
		free(arrOfStr);
		free(arr2);
		
	}
	else errmsg("error");

	return 0;
}

void countingsort(char **arr, char **arr2, int digit)
{
	int i;
	int *cntarr = (int *)malloc(sizeof(int) * MAXDIGIT);
	memset(cntarr, 0, sizeof(int)*MAXDIGIT);
	cntarr[0] = -1;
	for(i=0; i<DATANUM; i++)
	{
		if(arr[i][digit])
			cntarr[arr[i][digit] - '0' + 1]++;
		else
			cntarr[0]++;
	}
	for(i=1; i<MAXDIGIT; i++)
		cntarr[i] += cntarr[i-1];
	for(i=DATANUM-1; i>=0; i--)
	{
		if(arr[i][digit])
		{
			memcpy(arr2[cntarr[arr[i][digit] - '0' + 1]], arr[i], sizeof(char)*MAXLEN-1);
			cntarr[arr[i][digit] - '0' + 1]--;
		}
		else
		{
			memcpy(arr2[cntarr[0]], arr[i], sizeof(char)*MAXLEN-1);
			cntarr[0]--;
		}
	}
	for(i=0; i<DATANUM; i++)
		memcpy(arr[i], arr2[i], sizeof(char)*MAXLEN-1);
		
	free(cntarr);
}
