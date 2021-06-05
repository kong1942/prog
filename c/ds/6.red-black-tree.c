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
struct RBnode *delBalance(struct RBnode *node);
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

struct RBnode *delBalance(struct RBnode *node)
{
	if(node->parent == NULL) return node;

	struct RBnode *N = node;
	struct RBnode *P = node->parent;
	struct RBnode *S;
	if(N == P->Rchild) S = P->Lchild;
	else S = P->Rchild;

	if(S->color == 'R')
	{
		S->color = 'B';
		P->color = 'R';
		if(N == P->Rchild) rotateRight(P);
		else rotateLeft(P);
		delBalance(N);
	}
	else
	{
		struct RBnode *r = N;
		if(P->color == 'B'&& (S->Rchild == NULL || S->Rchild->color == 'B') && (S->Lchild == NULL || S->Lchild->color == 'B'))
		{
			S->color = 'R';
			delBalance(P);
		}
		else if(P->color == 'R' && (S->Rchild == NULL || S->Rchild->color == 'B') && (S->Lchild == NULL || S->Lchild->color == 'B'))
		{
			S->color = 'R';
			P->color = 'B';
			while(r->parent) {r = r->parent;}
			return r;
		}
		else if(N == P->Lchild && S->Lchild && S->Lchild->color == 'R' && (S->Rchild == NULL || S->Rchild->color == 'B'))
		{
			S->color = 'R';
			S->Lchild->color = 'B';
			rotateRight(S);
			delBalance(N);
		}
		else if(N == P->Rchild && S->Rchild && S->Rchild->color == 'R' && (S->Lchild == NULL || S->Lchild->color == 'B'))
		{
			S->color = 'R';
			S->Rchild->color = 'B';
			rotateLeft(S);
			delBalance(N);
		}
		else if(N == P->Rchild && S->Lchild && S->Lchild->color == 'R')
		{
			S->color = P->color;
			P->color = 'B';
			S->Lchild->color = 'B';
			rotateRight(P);
			while(r->parent) {r = r->parent;}
			return r;
		}
		else if(N == P->Lchild && S->Rchild && S->Rchild->color == 'R')
		{
			S->color = P->color;
			P->color = 'B';
			S->Rchild->color = 'B';
			rotateLeft(P);
			while(r->parent) {r = r->parent;}
			return r;
		}
	}
}

struct RBnode *delete(struct RBnode *root, int key)
{
	struct RBnode *q = root;
	char RL = '\0';
	while(q)
	{
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
			numOfNode--;
			struct RBnode *n, *r;
			int key;
			if(q->Rchild)
			{
				RL = 'R';
				n = q->Rchild;
				if(n->Lchild)
				{
					RL = 'L';
					while(n->Lchild) {n = n->Lchild;}
				}
				key = n->key;
				n->key = q->key;
				q->key = key;
				q = n;
				r = root;
				if(q->Rchild)
				{
					q->Rchild->parent = q->parent;
					if(q == q->parent->Rchild) q->parent->Rchild = q->Rchild;
					else q->parent->Lchild = q->Rchild;
					
					if(q->Rchild->color == 'R') q->Rchild->color = 'B';
					else r = delBalance(q->Rchild);
				}
				else //n->Rchild, Lchild == NULL
				{
					if(q == q->parent->Rchild) q->parent->Rchild = NULL;
					else q->parent->Lchild = NULL;
				}
			}
			else if(q->Lchild)
			{
				RL = 'L';
				n = q->Lchild;
				if(n->Rchild)
				{
					RL = 'R';
					while(n->Rchild) {n = n->Rchild;}
				}
				key = n->key;
				n->key = q->key;
				q->key = key;
				q = n;
				r = root;
				if(q->Lchild)
				{
					q->Lchild->parent = q->parent;
					if(q == q->parent->Rchild) q->parent->Rchild = q->Lchild;
					else q->parent->Lchild = q->Lchild;
					
					if(q->Lchild->color == 'R') q->Lchild->color = 'B';
					else r = delBalance(q->Lchild);
				}
				else //n->R, Lchild == NULL
				{
					if(q == q->parent->Rchild) q->parent->Rchild = NULL;
					else q->parent->Lchild = NULL;
				}
			}
			else //(q->Rchild == NULL && q->Lchild == NULL)
			{
				if(q == root)
				{
					free(q);
					return NULL;
				}
				else
				{
					if(q == q->parent->Rchild) q->parent->Rchild = NULL;
					else q->parent->Lchild = NULL;
					free(q);
					return root;
				}
			}
			free(q);
			return r;
		}
	}
	errmsg("delete error");
	return root;
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

void BreadthFirstSearch(struct RBnode *root)
{
	if(root == NULL) {errmsg("is empty"); return;}
	/*
	int height=1, lastHeight=-1, n, N;
	n = (int) pow(2, maxHeight+1);
	N = n;
	*/
	int head = 0, tail = 0;
	struct RBnode *p;
	struct RBnode **arr = (struct RBnode **)malloc(sizeof(struct RBnode) * (numOfNode+1));
	memset(arr, 0, sizeof(struct RBnode *) * (numOfNode+1));

	arr[tail] = root; tail++;
	while(head != tail)
	{
		/*
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
		*/

		p = arr[head];
		printf("%d ", p->key);
		if(p->Lchild) {arr[tail] = p->Lchild; tail++;}
		if(p->Rchild) {arr[tail] = p->Rchild; tail++;}
		/*
		else printf("< NULL >");

		for(int i=0; i<(n*2)-1; i++)
			printf("        ");
		*/
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
