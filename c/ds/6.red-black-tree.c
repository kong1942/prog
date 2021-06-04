#include "ds.h"
#include <math.h>
int first = TRUE;
int numOfNode = 0;
int maxHeight = 1;

struct RBnode
{
	int key;
	char color;
	struct RBnode *parent;
	struct RBnode *Lchild;
	struct RBnode *Rchild;
};

void init(struct RBnode *root);
void rotateRight(struct RBnode *pivot);
void rotateLeft(struct RBnode *pivot);
struct RBnode *balance(struct RBnode *node);
struct RBnode *insert(struct RBnode *root, int key);
struct RBnode *delete(struct RBnode *root, int key);
void getwd(char *line, char *wd);
void BreadthFirstSearch(struct RBnode *root);
void DepthFirstSearch(struct RBnode *root, char *mode);
void inorder(struct RBnode *root);
void preorder(struct RBnode *root);
void postorder(struct RBnode *root);
void traversal(struct RBnode *root);						//postorder traversal to free memery

int main()
{
	char line[MAXLEN];
	char wd[5];
	char *ptr;
	struct RBnode *root = NULL;

	while(fgets(line, MAXLEN, stdin))
	{
		rmNewline(line);
		if(*line)
		{
			ptr = line;
			getcommand(line, wd);
			if(!strcmp(wd, "in"))
			{
				while(*ptr && !isdigit(*ptr))  {ptr++;}
				if(*ptr)
				{
					root = insert(root, atoi(ptr));
				}
				else errmsg("insert error");
			}
			else if(!strcmp(wd, "del"))
			{}
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


void init(struct RBnode *root)
{
	root->color = 'R';
	root->parent = NULL;
	root->Lchild = NULL;
	root->Rchild = NULL;
}

void rotateRight(struct RBnode *pivot)
{
	struct RBnode *N = pivot->Lchild;
	struct RBnode *P = pivot->parent;
	pivot->Lchild = N->Rchild;
	if(pivot->Lchild) pivot->Lchild->parent = pivot;
	pivot->parent = N;
	N->Rchild = pivot;
	N->parent = P;
	if(P)
	{
		if(P->Rchild == pivot) P->Rchild = N;
		else P->Lchild = N;
	}
}

void rotateLeft(struct RBnode *pivot)
{
	struct RBnode *N = pivot->Rchild;
	struct RBnode *P = pivot->parent;
	pivot->Rchild = N->Lchild;
	if(pivot->Rchild) pivot->Rchild->parent = pivot;
	pivot->parent = N;
	N->parent = P;
	if(P)
	{
		if(P->Rchild == pivot) P->Rchild = N;
		else P->Lchild = N;
	}
	N->Lchild = pivot;
}

struct RBnode *balance(struct RBnode *node)
{
	//node = N, parent = P, uncle = U, grandparent = G
	//case1. root = black
	if(node->parent == NULL)
	{
		node->color = 'B';
		return node;
	}
	//case2. if P is black
	else if(node->parent->color == 'B')
	{
		struct RBnode *p = node;
		int height=1;
		while(p->parent) {p = p->parent; height++;}
		if(height > maxHeight) maxHeight = height;
		return p;
	}
	else
	{
		struct RBnode *P = node->parent;
		struct RBnode *U;
		struct RBnode *G = node->parent->parent;
		if(P == G->Rchild) U = G->Lchild;
		else U = G->Rchild;
		//case3. if P and U is red, then P, U = black, and G = red, balance(G)
		if(P->color == 'R' && U != NULL && U->color == 'R')
		{
			P->color = 'B';
			U->color = 'B';
			G->color = 'R';
			balance(G);
		}
		//case4_5. P is red and U is NULL or black
		else if(P->color == 'R' && (U == NULL || U->color == 'B'))
		{
			//case4. if N is P->R(L), P is G->L(R) then rotate P, rebalance P 
			if(node == P->Rchild && P == G->Lchild)
			{
				rotateLeft(P);
				balance(P);
			}
			else if(node == P->Lchild && P == G->Rchild)
			{
				rotateRight(P);
				balance(P);
			}
			//case5. if N is P->R(L), P is G->R(L) then P = black, G = red, rotate G, rebalance P 
			else 
			{
				P->color = 'B';
				G->color = 'R';
				if(node == P->Rchild && P == G->Rchild)
				{
					rotateLeft(G);
				}
				else if(node == P->Lchild && P == G->Lchild)
				{
					rotateRight(G);
				}
				balance(node);
			}
		}
	}
}

struct RBnode *insert(struct RBnode *root, int key)
{
	struct RBnode *p;
	if(root == NULL)
	{
		p = (struct RBnode *)malloc(sizeof(struct RBnode));
		init(p);
		p->key = key;
		if(first) {p->color = 'B'; first = FALSE;}
		numOfNode++;
		return p;
	}
	
	char RL = '\0';
	struct RBnode *q = root;
	while(q)
	{
		p = q;
		if(key > q->key)
		{
			RL = 'R';
			q = q->Rchild;
		}
		else if(key < q->key)
		{
			RL = 'L';
			q = q->Lchild;
		}
		else
		{
			errmsg("Duplicate value");
			return root;
		}
	}
	if(RL == 'R')
	{
		p->Rchild = insert(p->Rchild, key); 
		p->Rchild->parent = p;
		q = balance(p->Rchild);
	}
	else 
	{
		p->Lchild = insert(p->Lchild, key); 
		p->Lchild->parent = p; 
		q = balance(p->Lchild);
	}
	return q;
}

struct RBnode *delete(struct RBnode *root, int key);

void getwd(char *line, char *wd)
{
	char *p = line;
	char *q = wd;
	while(*p && isalpha(*p)) {p++;}
	while(*p && !isalpha(*p)) {p++;}
	while(q - wd < 5 && isalpha(*p)) {*q++ = *p++;}
	*q = '\0';
}

void BreadthFirstSearch(struct RBnode *root)
{
	if(root == NULL) {errmsg("is empty"); return;}
	int head=1, tail=1, height=1, lastHeight=-1, n, N;
	n = (int) pow(2, maxHeight+1);
	N = n;
	struct RBnode *p, *q;
	struct RBnode **arr = (struct RBnode **)malloc(sizeof(struct RBnode) * n);
	memset(arr, 0, sizeof(struct RBnode *) * n);

	arr[tail] = root; tail++;
	while(head != N)
	{
		height = (int) log2(head);						//print current level
		if(lastHeight != height) 
		{
			if(height != 0) printf("\n");
			printf("level: %d ", height);
			n /= 2;
			for(int i=0; i<n-1; i++)
				printf("        ");
		}
		lastHeight = height;
		

		p = arr[head];
		if(p)
		{
			printf("<%2d , %c>", p->key, p->color);
			if(p->Lchild) {arr[head*2] = p->Lchild; tail++;}
			if(p->Rchild) {arr[head*2+1] = p->Rchild; tail++;}
		}
		else printf("< NULL >");

		for(int i=0; i<(n*2)-1; i++)
			printf("        ");
		head++;
	}

	printf("\n");
}

void DepthFirstSearch(struct RBnode *root, char *wd)
{
	if(root == NULL) {errmsg("is empty"); return;}
	if(*wd == '\0' || !strcmp(wd, "in"))
	{
		inorder(root);
		printf("\n");
	}
	else if(!strcmp(wd, "pre"))
	{
		preorder(root);
		printf("\n");
	}
	else if(!strcmp(wd, "post"))
	{
		postorder(root);
		printf("\n");
	}
	else errmsg("DFS error");
}

void inorder(struct RBnode *root)
{
	if(root == NULL) {return;}
	inorder(root->Lchild);
	printf("%d ", root->key);
	inorder(root->Rchild);
}

void preorder(struct RBnode *root)
{
	if(root == NULL) {return;}
	printf("%d ", root->key);
	preorder(root->Lchild);
	preorder(root->Rchild);
}

void postorder(struct RBnode *root)
{
	if(root == NULL) {return;}
	postorder(root->Lchild);
	postorder(root->Rchild);
	printf("%d ", root->key);
}

void traversal(struct RBnode *root)
{

	if(root)
	{
		traversal(root->Lchild);
		traversal(root->Rchild);
		free(root);
	}
}
