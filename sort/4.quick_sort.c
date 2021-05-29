#include "sort.h"

int partition(void *arr, int head, int tail, char mode);
void quicksort(void *arr, int head, int tail, char mode);

int main(int argc, char **argv)
{
	int i=0;
	char line[MAXLEN];
	FILE *fp = fopen("data", "r");
	
	if(argc == 1 || !strcmp(argv[1], "-n"))
	{
		int *arrOfNum = (int *)malloc(sizeof(int) * DATANUM);
		while(fgets(line, MAXLEN, fp))
		{
			arrOfNum[i] = atoi(line);
			i++;
		}
		quicksort(arrOfNum, 0, DATANUM, 'n');
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
		quicksort(arrOfStr, 0, DATANUM, 's');
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

int partition(void *arr, int head, int tail, char mode)
{
	int i=head, j=head+1;
	int pivot = rand() % (tail - head) + head;
	if(mode == 'n')
	{
		int *arrN = (int *)arr;
		swap(&arrN[head], &arrN[pivot], mode);
		for(i=head+1; i<tail; i++)
		{
			if(arrN[i] < arrN[head])
			{	
				swap(&arrN[i], &arrN[j], mode);
				j++;
			}
		}
		j--;
	}
	else if(mode == 's')
	{
		char **arrS = (char **)arr;
		swap(&arrS[head], &arrS[pivot], mode);
		for(i=head+1; i<tail; i++)
		{
			if(strcmp(arrS[i], arrS[head]) < 0)
			{	
				swap(&arrS[i], &arrS[j], mode);
				j++;
			}
		}
		j--;
		swap(&arrS[head], &arrS[j], mode);
	}
	return j;
}

void quicksort(void *arr, int head, int tail, char mode)
{
	if(tail > head)
	{
		int pivot = partition(arr, head, tail, mode);
		quicksort(arr, head, pivot, mode);
		quicksort(arr, pivot+1, tail, mode);
	}
}
