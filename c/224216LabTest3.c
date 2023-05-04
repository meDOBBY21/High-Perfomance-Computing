#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int val;
  struct Node *l, *r;
};

struct kk
{
  struct Node *q;
  struct kk *p;
};

struct Node* CreateNode(int v)
{
  struct Node *n= NULL;
  n= (struct Node*)malloc(sizeof(struct Node));
  n->val= v;
  n->l= n->r= NULL;
}

struct kk* CreateKK(struct Node *n)
{
  struct kk *k= NULL;
  k= (struct kk*)malloc(sizeof(struct kk));
  k->q= n;
  k->p= NULL;
  return(k);
}

struct Node* Insert(struct Node *root, int v)
{
  if(root == NULL)
    return(CreateNode(v));
  if(v < root->val)
    root->l= Insert(root->l,v);
  else if(v > root->val)
    root->r= Insert(root->r,v);
  return(root);
}

struct kk* mm(struct kk *t, struct Node *n)
{
  struct kk *m= CreateKK(n);
  if(t == NULL)
    return(m);
  m->p= t;
  return(m);
}

struct kk* qq(struct kk **t)
{
  struct kk *m= NULL;
  if(*t == NULL)
    return(NULL);
  m= *t;
  *t= (*t)->p;
  return(m);
}

int Checker(struct kk *m)
{
  if(m == NULL)
    return(0);
  return(1);
}

void PrintInOrder(struct Node *root)
{
  if(root == NULL)
    return;
  PrintInOrder(root->l);
  printf("%d\n",root->val);
  PrintInOrder(root->r);
}
void postorder( struct node*);
int main()
{
  struct Node *root= NULL, *i= NULL;
  struct kk *p= NULL, *j= NULL;
  root= Insert(root,8);
  root= Insert(root,12);
  root= Insert(root,4);
  root= Insert(root,2);
  root= Insert(root,6);
  root= Insert(root,10);
  root= Insert(root,14);
  root= Insert(root,7);
  root= Insert(root,5);
  root= Insert(root,9);
  root= Insert(root,11);
  root= Insert(root,15);
  root= Insert(root,3);
  root= Insert(root,13);
  root= Insert(root,1);
  printf("%d",root->val);
  printf("postorder\n");
  postorder(root);
  
  p= mm(p,root);
  while(Checker(p))
  {
    j= qq(&p);
    i= j->q;
    printf("%d\n",i->val);
    if(i->r != NULL)
      p= mm(p, i->r);
    if(i->l != NULL)
      p= mm(p, i->l);
  }
void postorder(r)
{
 if (root==NULL)
 {
  return;
 }
  postorder(root->l);
  postorder(root->r);
  printf("%d\n",root->val);
}
  //Write your code here to print the tree in post order traversal
  //Clue: Similar loop. Use two struct *kk. In first one, mm first l and then r. Instead of printf, mm to second struct kk.
}
