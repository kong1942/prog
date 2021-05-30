//Parent		i / 2
//Left child		2 * i
//Right child		2 * i + 1
//Max Heap : any subtree => 	root > left child and right child
//Min Heap : 	...		root < left child and right child
#include "sort.h"

void maxheap(void *arr, int root, int tail, char mode);
void heapsort(void *arr, int root, char mode);					

int main(int argc, char **argv)
{
	int i=0;
	char line[MAXLEN];
	FILE *fp;
       	if(fp = fopen("data", "r") == NULL)
		errmsg("data error");
	
	if(argc == 1 || !strcmp(argv[1], "-n"))
	{
		int *arrOfNum = (int *)malloc(sizeof(int) * (DATANUM+1));
		i=1;
		while(fgets(line, MAXLEN, fp))
		{
			arrOfNum[i] = atoi(line);
			i++;
		}
		heapsort(arrOfNum, DATANUM, 'n');
		for(i=1; i<DATANUM+1; i++)
			printf("%d\n", arrOfNum[i]);
		free(arrOfNum);
	}
	else if(argc == 2 || !strcmp(argv[1], "-s"))
	{
		int len;
		char **arrOfStr = (char **)malloc(sizeof(char *) * (DATANUM+1));
		i=1;
		while(fgets(line, MAXLEN, fp))
		{
			len = strlen(line);
			if(line[len-1] == '\n') line[len-1] = '\0';
			arrOfStr[i] = strdup(line);
			i++;
		}
		heapsort(arrOfStr, DATANUM, 's');
		for(i=1; i<DATANUM+1; i++)
		{
			printf("%s\n", arrOfStr[i]);
			free(arrOfStr[i]);
		}
		free(arrOfStr);
	}
	else errmsg("error");

	return 0;
}

void maxheap(void *arr, int root, int tail, char mode)
{
	int max = root, left = root*2, right = root*2 + 1;
	if(mode == 'n')
	{
		int *arrN = (int *)arr;
		if(arrN[left] > arrN[max]) max = left;
		if(right <= tail && arrN[right] > arrN[max]) max = right;
		if(root != max) swap(&arrN[root], &arrN[max], mode);
	}
	else if(mode == 's')
	{
		char **arrS = (char **)arr;
		if(strcmp(arrS[left], arrS[max]) > 0) max = left;
		if(right <= tail && strcmp(arrS[right], arrS[max]) > 0) max = right;
		if(root != max) swap(&arrS[root], &arrS[max], mode);
	}
}

void heapsort(void *arr, int tail, char mode)
{
	if(tail != 2)
	{
		int root = tail/2;
		for(int i=root; i>0; i--)
			maxheap(arr, i, tail, mode);
		if(mode == 'n')
		{
			int *arrN = (int *)arr;
			swap(&arrN[1], &arrN[tail], mode);
		}
		else if(mode == 's')
		{
			char **arrS = (char **)arr;
			swap(&arrS[1], &arrS[tail], mode);
		}
		heapsort(arr, tail-1, mode);
	}
}
