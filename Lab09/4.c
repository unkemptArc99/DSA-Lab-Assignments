#include <stdio.h>
#include <stdlib.h>
struct node
{
	int key;
	int level;
	struct node *left;
	struct node *right;
};

struct node *newNode(int item,int l)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->level = l+1;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder_redefined(struct node *root,int *s)
{
    if(root!=NULL)
    {
        inorder_redefined(root->left,s);
        s[index_in]=root->key;
        index_in++;
        inorder_redefined(root->right,s);
    }
}

int totalnodes(struct node *root)
{
    if(root!=NULL)
    {
        int t=0;
        t++;
        return t+totalnodes(root->left)+totalnodes(root->right);
    }
    else
        return 0;
}

int main(int argc, char const *argv[])
{
	struct node *bintree;
	bintree=NULL;
	int tot;
	printf("Enter the total number of nodes you want to enter : ");
	scanf("%d",&tot);
	int in=0,don=0;
	while(don!=tot)
	{
		printf("Do you want to enter a node at index %d (y or n) : ",in);
		int c;
		scanf("%c",&c);
		if(c=='n')
			in++;
		else
		{
			if(in==0)
			{
				bintree=newNode(bintree)
			}
		}
	}
	int *s,no,i;
	no=totalnodes(bintree);
	s=(int *)malloc(no*sizeof(int));
    inorder_redefined(bintree,s);
    int flag=0;
    for(i=0;i<no-1;++i)
    {
    	if(a[i]>a[i+1])
    	{
    		flag=1;
    		break;
    	}
    }
    if(!flag)
    	printf("It is a binary search tree\n");
    else
    	printf("It is not a binary search tree\n");

	return 0;
}