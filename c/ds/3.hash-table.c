#include "ds.h"
#define HASHNUM 997

struct Lnode
{
	int key;
	struct Lnode *next;
};

int hash(int key);
struct Lnode *L_insert(struct Lnode *l, int key);					//insert at head
void insert(struct Lnode **hTab, int key);
struct Lnode *L_delete(struct Lnode *l, int key);
void delete(struct Lnode **hTab, int key);
void list(struct Lnode **hTab);
void traversal(struct Lnode **hTab);

int main()
{
	int len;
	char line[MAXLEN];
	char wd[5];
	char *ptr;
	struct Lnode **hTab = (struct Lnode **)malloc(sizeof(struct Lnode *) * HASHNUM);
	memset(hTab, 0, sizeof(struct Lnode *) * HASHNUM);

	while(fgets(line, MAXLEN, stdin))
	{
		rmNewline(line);
		if(*line)
		{
			ptr = line;
			getcommand(line, wd);
			if(!strcmp(wd, "inh"))
			{
				while(*ptr && !isdigit(*ptr)) {ptr++;}
				if(*ptr) insert(hTab, atoi(ptr));
				else errmsg("insert error");
			}
			else if(!strcmp(wd, "del"))
			{
				while(*ptr && !isdigit(*ptr)) {ptr++;}
				if(*ptr) delete(hTab, atoi(ptr));
				else errmsg("insert error");
			}
			else if(!strcmp(wd, "ls")) list(hTab);
			else if(!strcmp(wd, "exit")) break;
			else errmsg("error");
		}
	}

	traversal(hTab);
	return 0;
}

int hash(int key)
{
	return key % HASHNUM;
}

struct Lnode *L_insert(struct Lnode *l, int key)
{
	struct Lnode *p = (struct Lnode *)malloc(sizeof(struct Lnode));
	p->key = key;
	p->next = l;
	return p;
}

void insert(struct Lnode **hTab, int key)
{
	int n = hash(key);
	hTab[n] = L_insert(hTab[n], key);
}

struct Lnode *L_delete(struct Lnode *l, int key)
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

void delete(struct Lnode **hTab, int key)
{
	if(hTab == NULL) {errmsg("is empty"); return;}
	int n = hash(key);
	hTab[n] = L_delete(hTab[n], key);
}

void list(struct Lnode **hTab)
{
	if(hTab == NULL) {errmsg("is empty"); return;}
	struct Lnode *p;
	for(int i=0; i<HASHNUM; i++)
	{
		p = hTab[i];
		if(p) printf("%3d. ", i);
		while(p)
		{
			printf("%d ", p->key);
			p = p->next;
		}
		if(hTab[i]) printf("\n");
	}
}

void traversal(struct Lnode **hTab)
{
	struct Lnode *p;
	struct Lnode *q;
	for(int i=0; i<HASHNUM; i++)
	{
		p = hTab[i];
		while(p)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}
}
