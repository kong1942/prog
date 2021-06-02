#include "ds.h"

unsigned numOfNode = 0;

struct BSnode
{
	int key;
	struct BSnode *parent;
	struct BSnode *Lchild;
	struct BSnode *Rchild;
};

struct BSnode *insert(struct BSnode *root, int key);
struct BSnode *delete(struct BSnode *root, int key);
void BreadthFirstSearch(struct BSnode *root);
void DepthFirstSearch(struct BSnode *root, char *wd);
void getwd(char *linem, char *wd);
void inorder(struct BSnode *root);
void preorder(struct BSnode *root);
void postorder(struct BSnode *root);
void traversal(struct BSnode *root);

int main()
{
	char wd[5];
	char line[MAXLEN];
	char *ptr;
	struct BSnode *root = NULL;

	while(fgets(line, MAXLEN, stdin))
	{
		ptr = line;
		rmNewline(line);
		if(*line == '\0') continue;
		else
		{
			getcommand(line, wd);
			if(!strcmp(wd, "in"))
			{
				while(*ptr && !isdigit(*ptr))  {ptr++;}
				if(*ptr) root = insert(root, atoi(ptr));
				else errmsg("insert error");
			}
			else if(!strcmp(wd, "del"))
			{
				while(*ptr && !isdigit(*ptr))  {ptr++;}
				if(*ptr) root = delete(root, atoi(ptr));
				else errmsg("insert error");
			}
			else if(!strcmp(wd, "BFS"))
			{
				BreadthFirstSearch(root);
			}
			else if(!strcmp(wd, "DFS"))
			{
				getwd(line, wd);
				DepthFirstSearch(root, wd);
			}
			else if(!strcmp(wd, "exit")) break;
			else errmsg("error");
		}
	}
	traversal(root);
	return 0;
}

struct BSnode *insert(struct BSnode *root, int key)
{
	struct BSnode *p;
	if(root == NULL)
	{
		numOfNode++;
		p = (struct BSnode *)malloc(sizeof(struct BSnode));
		p->key = key;
		p->parent = NULL;
		p->Lchild = NULL;
		p->Rchild = NULL;
		return p;
	}
	char RL = '\0';
	struct BSnode *q = root;
	while(q)
	{
		if(key > q->key)
		{
			RL = 'R';
			p = q;
			q = q->Rchild;
		}
		else if(key < q->key)
		{
			RL = 'L';
			p = q;
			q = q->Lchild;
		}
		else 
		{
			errmsg("insert error: same key");
			return root;
		}
	}
	if(RL == 'R') {p->Rchild = insert(p->Rchild, key); p->Rchild->parent = p;}
	else if(RL == 'L') {p->Lchild = insert(p->Lchild, key); p->Lchild->parent = p;}
	return root;
}

struct BSnode *delete(struct BSnode *root, int key)
{
	if(root == NULL) {errmsg("is empty"); return NULL;}
	char RL = '\0';
	struct BSnode *p;
	struct BSnode *q = root;
	while(q)
	{
		if(key > q->key)
		{
			RL = 'R';
			p = q;
			q = q->Rchild;
		}
		else if(key < q->key)
		{
			RL = 'L';
			p = q;
			q = q->Lchild;
		}
		else 
		{
			numOfNode--;
			struct BSnode *n;
			if(q->Rchild)
			{
				n = q->Rchild;
				if(n->Lchild == NULL)
				{
					n->parent = p;
					if(RL == 'R') p->Rchild = n;
					else p->Lchild = n;
				}
				else
				{
					while(n->Lchild) {n = n->Lchild;}
					n->parent->Lchild = n->Rchild;
					n->parent = p;
					n->Rchild = q->Rchild;
					n->Lchild = q->Lchild;
					if(RL == 'R') p->Rchild = n;
					else p->Lchild = n;
				}
			}
			else if(q->Lchild)
			{
				n = q->Lchild;
				if(n->Rchild == NULL)
				{
					n->parent = p;
					if(RL == 'R') p->Rchild = n;
					else p->Lchild = n;
				}
				else
				{
					while(n->Rchild) {n = n->Rchild;}
					n->parent->Rchild = n->Lchild;
					n->parent = p;
					n->Rchild = q->Rchild;
					n->Lchild = q->Lchild;
					if(RL == 'R') p->Rchild = n;
					else p->Lchild = n;
				}
			}
			else 
			{
				if(RL == 'R') p->Rchild = NULL;
				else p->Lchild = NULL;
			}
			free(q);
			return root;
		}
	}
	errmsg("Not found");
	return root;
}

void BreadthFirstSearch(struct BSnode *root)						//queue
{
	if(root == NULL) {errmsg("is empty"); return;}
	struct BSnode **arr = (struct BSnode **)malloc(sizeof(struct BSnode *) * (numOfNode + 1));
	memset(arr, 0, sizeof(struct BSnode *) * (numOfNode + 1));
	int head = 0;
	int tail = 0;
	arr[tail] = root; tail++;
	while(arr[head])
	{
		struct BSnode *n = arr[head];
		printf("%d\n", n->key);
		head++;
		if(n->Lchild) {arr[tail] = n->Lchild; tail++;}
		if(n->Rchild) {arr[tail] = n->Rchild; tail++;}
	}
	free(arr);
}

void DepthFirstSearch(struct BSnode *root, char *wd)						//stack
{
	if(root == NULL) {errmsg("is empty"); return;}
	if(*wd == '\0' || !strcmp(wd, "in"))
	{
		inorder(root);
	}
	else if(!strcmp(wd, "pre"))
	{
		preorder(root);
	}
	else if(!strcmp(wd, "post"))
	{
		postorder(root);
	}
	else errmsg("DFS error");
}

void getwd(char *line, char *wd)
{
	char *p = line;
	char *q = wd;
	while(*p && isalpha(*p)) {p++;}
	while(*p && !isalpha(*p)) {p++;}
	while(q - wd < 5 && isalpha(*p)) {*q++ = *p++;}
	*q = '\0';
}

void inorder(struct BSnode *root)
{
	if(root == NULL) {return;}
	inorder(root->Lchild);
	printf("%d\n", root->key);
	inorder(root->Rchild);
}

void preorder(struct BSnode *root)
{
	if(root == NULL) {return;}
	printf("%d\n", root->key);
	preorder(root->Lchild);
	preorder(root->Rchild);
}

void postorder(struct BSnode *root)
{
	if(root == NULL) {return;}
	postorder(root->Lchild);
	postorder(root->Rchild);
	printf("%d\n", root->key);
}

void traversal(struct BSnode *root)
{
	if(root == NULL) {return;}
	postorder(root->Lchild);
	postorder(root->Rchild);
	free(root);
}


