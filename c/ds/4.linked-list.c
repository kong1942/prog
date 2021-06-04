#include "ds.h"

struct Lnode
{
	int key;
	struct Lnode *next;
};

struct Lnode *insertAtHead(struct Lnode *l, int key);						//insert at head
struct Lnode *insertAtTail(struct Lnode *l, int key);						//insert at tail
struct Lnode *delete(struct Lnode *l, int key);
void list(struct Lnode *l);
void traversal(struct Lnode *l);

int main()
{
	int len;
	char line[MAXLEN];
	char wd[5];
	char *ptr;
	struct Lnode *l = NULL;
	
	while(fgets(line, MAXLEN, stdin))
	{
		rmNewline(line);
		if(*line)
		{
			ptr = line;
			getcommand(line, wd);
			if(!strcmp(wd, "inh"))
			{
				while(*ptr && !isdigit(*ptr))  {ptr++;}
				if(*ptr) l = insertAtHead(l, atoi(ptr));
				else errmsg("insert error");
			}
			else if(!strcmp(wd, "int"))
			{
				while(*ptr && !isdigit(*ptr))  {ptr++;}
				if(*ptr) l = insertAtTail(l, atoi(ptr));
				else errmsg("insert error");
			}
			else if(!strcmp(wd, "del"))
			{
				while(*ptr && !isdigit(*ptr))  {ptr++;}
				if(*ptr) l = delete(l, atoi(ptr));
				else errmsg("delete error");
			}
			else if(!strcmp(wd, "ls")) list(l);
			else if(!strcmp(wd, "exit")) break;
			else errmsg("command error");
		}
	}
	traversal(l);

	return 0;
}

struct Lnode *insertAtHead(struct Lnode *l, int key)
{
	struct Lnode *p = (struct Lnode *)malloc(sizeof(struct Lnode));
	p->key = key;
	p->next = l;
	return p;
}

struct Lnode *insertAtTail(struct Lnode *l, int key)
{
	if(l == NULL) l = insertAtHead(l, key);
	else
	{
		struct Lnode *p = l;
		while(p->next) {p = p->next;}
		p->next = insertAtHead(p->next, key);
	}
	return l;
}

struct Lnode *delete(struct Lnode *l, int key)
{
	if(l == NULL) {errmsg("is empty"); return NULL;}
	struct Lnode *p = l;
	struct Lnode *q;
	if(p->key == key)
	{
		q = p->next;
		free(p);
		return q;
	}
	while(p)
	{
		if(p->next && p->next->key == key)
		{
			q = p->next;
			p->next = q->next;
			free(q);
			return l;
		}
		p = p->next;
	}
	errmsg("Not found");
	return l;
}

void list(struct Lnode *l)
{
	if(l == NULL) {errmsg("is empty"); return;}
	struct Lnode *p = l;
	while(p)
	{
		printf("%d ", p->key);
		p = p->next;
	}
	printf("\n");
}

void traversal(struct Lnode *l)
{
	struct Lnode *p = l;
	struct Lnode *q;
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
}
