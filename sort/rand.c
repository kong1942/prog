#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL)); rand();
	FILE *fp = fopen("data", "w");
	for(int i = 0; i < 1e4; i++)
		fprintf(fp, "%d\n", rand());
	fclose(fp);
	return 0;
}
