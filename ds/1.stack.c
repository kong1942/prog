#include "ds.h"

struct stack
{
	int *key;
	int *top;
	int *bottom;
};

void getcommand(char *line, char *command);
void init(struct stack *s);
void push(struct stack *s, int key);
void pop(struct stack *s);
int full(struct stack *s);
int empty(struct stack *s);
void list(struct stack *s);

int main()
{
	int len, key;
	char wd[5];
	char line[MAXLEN];
	char *ptr;
	struct stack *s = (struct stack *)malloc(sizeof(struct stack));
	init(s);

	while(fgets(line, MAXLEN, stdin))
	{
		len = strlen(line);
		if(line[len-1] == '\n') line[len-1] = '\0';
		if(!strcmp(line, "pop"))
			pop(s);
		else
		{
			getcommand(line, wd);
			if(!strcmp(wd, "push"))
			{
				ptr = line;
				while(*ptr && !isdigit(*ptr)) {ptr++;}
				if(*ptr)
				{
					key = atoi(ptr);
					push(s, key);
				}
				else errmsg("push error");
			}
			else if(!strcmp(wd, "list"))
				list(s);
			else if(!strcmp(wd, "exit"))
				break;
			else if(*line == '\0')
				continue;
			else
				errmsg("error");
		}
	}

	free(s->key);
	free(s);
	return 0;
}

void getcommand(char *line, char *command)
{
	char *ptr = line;
	char *qtr = command;
	for(int i=0; i<4; i++)
		*qtr++ = *ptr++;
	*qtr = '\0';
}

void init(struct stack *s)
{
	s->key = (int *)malloc(sizeof(int) * DATANUM);
	memset(s->key, 0, sizeof(int) * DATANUM);
	s->top = s->key;
	s->bottom = s->key;
}

void push(struct stack *s, int key)
{
	if(full(s))
		return;
	*(s->top++) = key;
}

void pop(struct stack *s)
{
	if(empty(s))
		return;
	printf("%d\n", *(--s->top));
	*s->top = 0;
}

int full(struct stack *s)
{
	if(s->top - s->bottom != DATANUM)
		return 0;
	errmsg("is full");
	return 1;
}

int empty(struct stack *s)
{
	if(s->top != s->bottom)
		return 0;
	errmsg("is empty");
	return 1;
}

void list(struct stack *s)
{
	if(!empty(s))
		for(int i=s->top-s->bottom - 1; i>=0; i--)
			printf("%d\n", s->key[i]);
}
