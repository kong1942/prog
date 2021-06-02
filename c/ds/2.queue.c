#include "ds.h"

struct queue
{
	int *key;
	int *head;
	int *tail;
};

void getcommand(char *line, char *command);
void init(struct queue *q);
void enqueue(struct queue *q, int key);
void dequeue(struct queue *q);
int full(struct queue *q);
int empty(struct queue *q);
void list(struct queue *q);

int main()
{
	int len;
	char line[MAXLEN];
	char *ptr;
	char wd[5];
	struct queue *q = (struct queue *)malloc(sizeof(struct queue));
	init(q);

	while(fgets(line, MAXLEN, stdin))
	{
		len = strlen(line);
		if(line[len-1] == '\n') line[len-1] = '\0';
		if(*line == '\0') continue;
		else 
		{
			getcommand(line, wd);
			if(!strcmp(wd, "enq"))
			{
				ptr = line;
				while(*ptr && !isdigit(*ptr)) {ptr++;}
				if(*ptr) enqueue(q, atoi(ptr));
				else errmsg("enqueue error");
			}
			else if(!strcmp(wd, "deq")) dequeue(q);
			else if(!strcmp(wd, "ls")) list(q);
			else if(!strcmp(wd, "exit")) break;
			else errmsg("command error");
		}
	}
	free(q->key);
	free(q);
	return 0;
}

void getcommand(char *line, char *command)
{
	char *ptr = line;
	char *qtr = command;
	while(qtr - command < 5 && isalpha(*ptr)) {*qtr++ = *ptr++;}
	*qtr = '\0';
}

void init(struct queue *q)
{
	q->key = (int *)malloc(sizeof(int) * DATANUM);
	memset(q->key, 0, sizeof(int) * DATANUM);
	q->head = q->key;
	q->tail = q->key;
}

void enqueue(struct queue *q, int key)
{
	if(full(q)) return;
	*(q->tail++) = key;
	if(q->tail - q->key == DATANUM) q->tail = q->key;
}

void dequeue(struct queue *q)
{
	if(empty(q)) return;
	printf("%d\n", *q->head);
	*(q->head++) = 0;
	if(q->head - q->key == DATANUM) q->head = q->key;
}

int full(struct queue *q)
{
	if(*q->tail == 0 || q->tail != q->head && q->tail - q->head != DATANUM) return FALSE;
	errmsg("is full");
	return TRUE;
}

int empty(struct queue *q)
{
	if(*q->head != 0 || q->head != q->tail && q->head - q->tail != DATANUM) return FALSE;
	errmsg("is empty");
	return TRUE;
}

void list(struct queue *q)
{
	if(empty(q)) return;
	int *ptr = q->head;
	printf("%d ", *ptr++);
	while(ptr != q->tail)
	{
		printf("%d ", *ptr++);
		if(ptr - q->key == DATANUM) ptr = q->key;
	}
	printf("\n");
}
