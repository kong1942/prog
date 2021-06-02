#include "sort.h"

void merge(void *arr, int head, int tail, char mode);
void mergesort(void *arr, int head, int tail, char mode);

int main(int argc, char **argv)
{
	int i=0;
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
		mergesort(arrOfNum, 0, DATANUM, 'n');
		for(i=0; i<DATANUM; i++)
			printf("%d\n", arrOfNum[i]);
		free(arrOfNum);
	}
	else if(argc == 2 || !strcmp(argv[1], "-s"))
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
		mergesort(arrOfStr, 0, DATANUM, 's');
		for(i=0; i<DATANUM; i++)
		{
			printf("%s\n", arrOfStr[i]);
			free(arrOfStr[i]);
		}
		free(arrOfStr);
	}
	else errmsg("error");

	return 0;
}

void merge(void *arr, int head, int tail, char mode)
{
	int partition = (head + tail)/2;
	int i=head, j=partition, k=0;
	if(mode == 'n')
	{
		int *arrN = (int *)arr;
		int *arr2 = (int *)malloc(sizeof(int) * (tail-head));
		for(k=0; k<(tail-head); k++)
		{
			if(j == tail || i < partition && arrN[i] <= arrN[j])
			{
				arr2[k] = arrN[i];
				i++;
			}
			else if(i == partition || j < tail && arrN[j] < arrN[i])
			{
				arr2[k] = arrN[j];
				j++;
			}
		}
		memcpy(&arrN[head], arr2, sizeof(int)*(tail-head));
		free(arr2);
	}
	else if(mode == 's')
	{
		char **arrS = (char **)arr;
		char **arr2 = (char **)malloc(sizeof(char *) * (tail-head));
		for(k=0; k<(tail-head); k++)
		{
			if(j == tail || i < partition && strcmp(arrS[i], arrS[j]) <= 0)
			{
				arr2[k] = strdup(arrS[i]);
				i++;
			}
			else if(i == partition || j < tail && strcmp(arrS[j], arrS[i]) < 0)
			{
				arr2[k] = strdup(arrS[j]);
				j++;
			}
		}
		
		for(i=0; i<(tail-head); i++)
		{
			free(arrS[i+head]);
			arrS[i+head] = strdup(arr2[i]);
			free(arr2[i]);
		}
		free(arr2);
	}
}

void mergesort(void *arr, int head, int tail, char mode)
{
	if(tail-1 > head)
	{
		int partition = (head + tail)/2;
		mergesort(arr, head, partition, mode);
		mergesort(arr, partition, tail, mode);
		merge(arr, head, tail, mode);
	}
}
