//IMPLEMENTATION OF AVL BINARY SEARCH TREES
//IN A AVL TREE THE MODULUS OF DIFFRENCE IN HEIGHT OF SUBTREES IS LESS THAN OR EQUAL TO ONE
//IT FULFILLS OUR PURPOSE OF KEEPING THE TREE BALANCED AND SHALLOW
//AS A RESULT THE SEARCH TIME IN AN AVL TREE IS VERY LESS i.e. O(log n)
#include<stdio.h>
#include<stdlib.h>
int f=0,t=1,ro;//THESE VARIABLES ARE HELPFUL IN CHECKING CERTAIN TEST CONDITIONS
struct node{
	int key;
	struct node *left;//POINTER FOR THE LEFT CHILD
	struct node *right;//POINTER FOR THE RIGHT CHILD
	struct node *parent;//POINTER FOR PARENT
		};
		typedef struct node *NODEPTR;
//FUNCTION TO CREATE A NODE
NODEPTR getnode()
{
	NODEPTR p=(NODEPTR) malloc(sizeof(struct node));
	p->left=NULL;
	p->right=NULL;
	p->parent=NULL;
	return p;
}
//FUNCTION TO FREE A NODE AFTER BEING DELETED
int freenode(n)
NODEPTR n;
{
	free(n);
	return 0;
}
//FUNCTION TO FIND THE HEIGHT OF A NODE IN THE TREE(HEIGHT OF LEAF IS 0)
int height(n)
NODEPTR n;
{
	int hl,hr;
	if(n==NULL)
	return -1;
	else
	{
		hl=height(n->right);
		hr=height(n->left);
		if(hl>hr)
		return (1+hl);
		else
		return (1+hr);
	}
}
//RECURSIVE FUNCTION TO CHECK WHETHER A NODE IS PRESENT OR NOT OR TO RETURN THE PARENT OF A NEW NODE AS PER THE USER CHOICE
NODEPTR find(r,k)
NODEPTR r;
int k;
{
	if(k==r->key)
	return r;
	if(k<r->key)//WHEN THE ELEMENT IS SMALLER THAN THE NODE KEY
	{
		if(r->left!=NULL)
		return find(r->left,k);
		else
		{
			if(f==1)
			return NULL;//WHEN THE USER WANTS TO CHECK THE PRESENCE OF A NODE
			else
			return r;//WHEN THE USER WANTS TO FIND PARENT FOR A NEW NODE
		}
	}
	else//WHEN THE ELEMENT IS GREATER THAN THE NODE KEY
	{
		if(r->right!=NULL)
		return find(r->right,k);
		else
		{
			if(f==1)
			return NULL;//WHEN THE USER WANTS TO CHECK THE PRESENCE OF A NODE
			else
			return r;//WHEN THE USER WANTS TO FIND PARENT FOR A NEW NODE
		}
	}
}
//FUNCTION TO ROTATE A NODE TO ITS RIGHT DURING REBALANCING THE LEFT OR REBALANCING THE CHILD OF THE RIGHT
NODEPTR rotateRight(r,n)
NODEPTR r;
NODEPTR n;
{
	NODEPTR p;
	int i=0;
	p=n->left;
	if(n->parent==NULL)//WHEN THE NODE IS PARENT
	{
		p->parent=NULL;
		i++;
	}
	else
	{
		p->parent=n->parent;
		if(n->key<(n->parent)->key)
		(n->parent)->left=p;
		else
		(n->parent)->right=p;
	}
	if(p->right!=NULL)
	{
		n->left=p->right;
		(p->right)->parent=n;
	}
	else
	n->left=NULL;
	p->right=n;
	n->parent=p;
	if(i)//TO CHECK IF ROOT IS TO BE SENT
	return p;
	return r;
}
//FUNCTION TO ROTATE A NODE TO ITS RIGHT DURING REBALANCING THE LEFT OR REBALANCING THE CHILD OF THE RIGHT
NODEPTR rotateLeft(r,n)
NODEPTR r;
NODEPTR n;
{
	NODEPTR p;
	int i=0;
	p=n->right;
	if(n->parent==NULL)//WHEN THE NODE IS PARENT
	{
		p->parent=NULL;
		i++;
	}
	else
	{
		p->parent=n->parent;
		if(n->key<(n->parent)->key)
		(n->parent)->left=p;
		else
		(n->parent)->right=p;
	}
	n->parent=p;
	if(p->left!=NULL)
	{
		n->right=p->left;
		(p->left)->parent=n;
	}
	else
	n->right=NULL;
	p->left=n;
	if(i)//TO CHECK IF ROOT IS TO BE SENT
	return p;
	return r;
}
//WHEN THE LEFT SIDE IS GREATER THAN RIGHT BY 2
NODEPTR rebalanceRight(r,n)
NODEPTR r;
NODEPTR n;
{
	NODEPTR p,t;
	p=n->left;
	if(height(p->right)>height(p->left))//TO BALANCE IF HEIGHT OF RIGHT OF LEFT CHILD OF THE NODE IS GREATER THAN HEIGHT OF LEFT OF THE SAME
	t=rotateLeft(r,p);
	t=rotateRight(r,n);
	return t;
}
//WHEN THE RIGHT SIDE IS GREATER THAN LEFT BY 2
NODEPTR rebalanceLeft(r,n)
NODEPTR r;
NODEPTR n;
{
	NODEPTR p,t;
	p=n->right;
	if(height(p->left)>height(p->right))//TO BALANCE IF HEIGHT OF LEFT OF RIGHT CHILD OF THE NODE IS GREATER THAN HEIGHT OF RIGHT OF THE SAME
	t=rotateRight(r,p);
	t=rotateLeft(r,n);
	return t;
}
//FUNCTION TO REBALNCE THE HEIGHTS
NODEPTR rebalance(r,n)
NODEPTR r;
NODEPTR n;
{
	NODEPTR p,t;
	p=n->parent;
	t=r;
	if(n->right==NULL && n->left==NULL)
	t=r;
	else
	if(height(n->left)>height(n->right)+1)
	t=rebalanceRight(r,n);
	else
	if(height(n->right)>height(n->left)+1)
	t=rebalanceLeft(r,n);
	if(p!=NULL)
	t=rebalance(t,p);
	return t;
}
//FUNCTION TO INSERT A NEW NODE
NODEPTR insert(r,k)
NODEPTR r;
int k;
{
	NODEPTR n,n1;
	n=getnode();
	n->key=k;
	if(r==NULL)//WHEN THE TREE IS EMPTY
	{
		n->parent=NULL;
		r=n;
		return n;
	}
	n1=find(r,k);//TO FIND THE PARENT
	n->parent=n1;
	if(n->key<n1->key)//TO FIND THE SIDE TOWARDS WHICH THE NODE IS TO BE UPDATED
	n1->left=n;
	else
	n1->right=n;
	return r;
}
//FUNCTION THAT RETURN A NODE TOWARDS RIGHT GREATER THAN THE GIVEN NODE BUT SMALLER THAN THE OTHER NODES GREATER THAN THE GIVEN NODE
NODEPTR leftdescendent(n)
NODEPTR n;
{
	if(n->left!=NULL)
	return leftdescendent(n->left);
	else
	return n;
}
//FUNCTION THAT RETURN A NODE UPWARDS LEFT GREATER THAN THE GIVEN NODE BUT SMALLER THAN THE OTHER NODES GREATER THAN THE GIVEN NODE
NODEPTR rightancestor(n)
NODEPTR n;
{
	if(n->key<(n->parent)->key)
	return n->parent;
	else
	if(n->parent==NULL)//WHEN IT IS THE ROOT ITSELF
	return NULL;
	else
	return rightancestor(n->parent);
}
//FUNCTION THAT RETURNS THE NODE JUST GRATER THAN THE GIVEN NODE
NODEPTR next(n)
NODEPTR n;
{
	if(n->right!=NULL)
	return leftdescendent(n->right);
	else
	return rightancestor(n);
}
//FUNCTION TO DELETE A NODE FROM THE TREE

NODEPTR delete(r,n)
NODEPTR n,r;
{
	NODEPTR n1;
	if(n==r)//WHEN THE ROOT IS REMOVED AND REPLACED
	{
		if(n->right==NULL && n->left==NULL)//WHEN THERE IS A SINGLE ROOT
		{
			t=1;
			freenode(n);
			return NULL;
		}
		else
		if(n->right==NULL)//WHEN THE RIGHT SUB-TREE OF THE ROOT IS ABSENT
		{
			n1=n->left;
			n1->parent=NULL;
			freenode(n);
			return n1;
		}
		else
		if(n->left==NULL)//WHEN THE LEFT SUB-TREE OF THE ROOT IS ABSENT
		{
			n1=n->right;
			n1->parent=NULL;
			freenode(n);
			return n1;
		}
		else
		{
			n1=next(n);
			if((n1->parent)->left==n1)
			{
				(n1->parent)->left=NULL;
				n1->parent=NULL;
			}
			else
			{
				n1->left=n->left;
				(n->left)->parent=n1;
				n1->parent=NULL;
				freenode(n);
				return n1;
			}
		}
	}
	else
	if(n->right==NULL && n->left==NULL)//WHEN THE NODE TO BE DELETED IS A LEAF
	{
		if(n->key<((n->parent)->key))
		(n->parent)->left=NULL;
		else
		(n->parent)->right=NULL;
		n1=(n->parent)->parent;
		freenode(n);
		return n1;
	}
	else
	if(n->right==NULL)
	{
		(n->left)->parent=n->parent;
		if(n->key<((n->parent)->key))
		(n->parent)->left=n->left;
		else
		(n->parent)->right=n->left;
		n1=(n->parent)->parent;
		freenode(n);
		return n1;
	}
	else
	{
		n1=next(n);
		if(n1==n->right)
		{
			n1->parent=n->parent;
			if(n->key<((n->parent)->key))
			(n->parent)->left=n1;
			else
			(n->parent)->right=n1;
			if(n->left!=NULL)
			{
				(n->left)->parent=n1;
				n1->left=n->left;
			}
			freenode(n);
			return n1->parent;
		}
		(n1->parent)->left=NULL;
		n1->parent=n->parent;
		if(n->key<((n->parent)->key))
		(n->parent)->left=n1;
		else
		(n->parent)->right=n1;
		(n->left)->parent=n1;
		(n->right)->parent=n1;
		n1->left=n->left;
		n1->right=n->right;
		freenode(n);
		return n1->parent;
	}
	(n->left)->parent=n1;
	(n->right)->parent=n1;
	n1->left=n->left;
	n1->right=n->right;
	if(n==r)
	{
		freenode(n);
		return n1;
	}
	freenode(n);
	return n1->parent;
}
//FUNCTION TO PERFORM LOCAL SEARCH
int search(r,x,y)
int x,y;//LIMITING ELEMENTS
NODEPTR r;
{
	NODEPTR n1,n;
	f=1;
	n=find(r,x);
	if(n==NULL)
	{
		f=0;
	    n=find(r,x);
		if(n->key<x)
		n=next(n);
	}
	n1=next(n);
	printf("%d\t",n->key);
	while(n1->key<=y)
	{
		printf("%d\t",n1->key);
		n1=next(n1);
		if(n1==NULL)
		{
			printf("\n");
			return 0;
		}
	}
	printf("\n");
	return 0;
}
//FUNCTION TO MAINTAIN THE AVL PROPERTY AFTER EACH INSERTION
NODEPTR avlinsert(r,k)
NODEPTR r;
int k;
{
	NODEPTR n;
	n=find(r,k);
	n=rebalance(r,n);
	return n;
}
//FUNCTION TO MAINTAIN THE AVL PROPERTY AFTER EACH DELETION
NODEPTR avldelete(r,k)
NODEPTR r;
NODEPTR k;
{
	NODEPTR n;
	n=rebalance(r,k);
	return n;
}
//FUNCTION FOR INORDER TRAVERSAL
int inorder(r)
NODEPTR r;
{

	if(r!=NULL)
	{
		inorder(r->left);
		printf("%d ",r->key);
		inorder(r->right);
	}
	return 0;
}
//FUNCTION FOR PREORDER TRAVERSAL
int preorder(r)
NODEPTR r;
{
	if(r!=NULL)
	{
		printf("%d ",r->key);
		preorder(r->left);
		preorder(r->right);
	}
	return 0;
}
//FUNCTION FOR POSTORDER TRAVERSAL
int postorder(r)
NODEPTR r;
{
	if(r!=NULL)
	{
		postorder(r->left);
		postorder(r->right);
		printf("%d ",r->key);
	}
	return 0;
}
//main FUNCTION TO CALL THE APPROPRIATE FUNCTIONS AS PER THE USER'S CHOICE
int main()
{
	NODEPTR root=NULL,n=NULL;
	int i=1,ch,k,a,b,h;
	printf("@@@@@@@MENU@@@@@@@\n");
	printf("1.TO INSERT A NODE\n");
	printf("2.TO DELETE A NODE\n");
	printf("3.TO PERFORM LOCAL SEARCH\n");
	printf("4.TO CHECK WHETHER A NODE IS PRESENT\n");
	printf("5.TO FIND THE NEXT NODE\n");
	printf("6.TO FIND THE HEIGHT OF A NODE\n");
	printf("7.TO TRAVERSE INORDER\n");
	printf("8.TO TRAVERSE PREORDER\n");
	printf("9.TO TRAVERSE POSTORDER\n");
	printf("10.TO STOP\n");
	while(i)
	{
		printf("Enter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:printf("Enter the node key:");
				   scanf("%d",&k);
				   root=insert(root,k);
				   root=avlinsert(root,k);
				   ro=root->key;
				   preorder(root);
				   printf("\n");
				   break;
			case 2:printf("Enter the node to be deleted:");
				   scanf("%d",&k);
				   printf("%d%d%d%d\n",root->key,ro,(root->left)->key,(root->right)->key);
				   if(ro==k)
				   {
					   n=find(root,k);
					   root=delete(root,n);
					   root=avldelete(root,root);
					   if(root!=NULL)
					   ro=root->key;
				   }
				   else
				   {
					   n=find(root,k);
					   n=delete(root,n);
					   root=avldelete(root,n);

				   }
				   preorder(root);
				   printf("\n");
				   break;
			case 3:printf("Enter the range:");
				   scanf("%d%d",&a,&b);
				   search(root,a,b);
				   break;
			case 4:printf("Enter the node to find:");
				   scanf("%d",&k);
				   f=1;
				   n=find(root,k);
				   if(n==NULL)
				   printf("NOT PRESENT\n");
				   else
				   printf("PRESENT\n");
				   f=0;
				   break;
			case 5:printf("Enter the node:");
				   scanf("%d",&k);
				   f=1;
				   n=find(root,k);
				   if(n!=NULL)
				   {
					   n=next(n);
					   if(n!=NULL)
					   printf("%d\n",n->key);
				     else
					   printf("IT IS THE LARGEST ELEMENT\n");
					   f=0;
				   }
				   else
				   {
					   f=0;
					   n=find(root,k);
					   if(n->key>k)
					   printf("%d\n",n->key);
					   else
					   {
						   n=next(n);
						   printf("%d\n",n->key);
					   }
				   }
				   break;
			case 6:printf("Enter the node:");
				   scanf("%d",&k);
				   n=find(root,k);
				   h=height(n);
				   printf("Height:%d\n",h);
				   break;
			case 7:inorder(root);
				   printf("\n");
				   break;
			case 8:preorder(root);
				   printf("\n");
				   break;
			case 9:postorder(root);
				   printf("\n");
				   break;
			case 10:i=0;
				   break;
		}
	}
}
//END OF PROGRAM
