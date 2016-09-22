/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 06 - Question 3 - Function file
Date : 22/09/2016
*********************************************************/
#include "C_header.h"

void append ( struct node **q, int num )
{
	struct node *temp, *r ;

	if ( *q == NULL )  /* if the list is empty, create first node */
	{
		temp = ( struct node * ) malloc ( sizeof ( struct node ) ) ;
		temp -> data = num ;
		temp -> link = NULL ;
		int flag=0;
		while(flag==0)
		{
			printf("Enter the random node to assign (0-indexed) : ");
			int r;
			scanf("%d",&r);
			int i;
			struct node *temp1;
			temp1=(struct node *)malloc(sizeof(struct node));
			temp1=*q;
			for(i=0;i<=r;++i)
			{
				if(temp1->link==NULL)
					
				temp1=temp1->link;
			}
		}
		*q = temp ;
	}
	else
	{
		temp = *q ;//temp to head

		/* go to last node */
		while ( temp -> link != NULL )
			temp = temp -> link ;

		/* add node at the end */
		r = ( struct node * ) malloc ( sizeof ( struct node ) ) ;
		r -> data = num ;
		r -> link = NULL ;
		temp -> link = r ;//temp is pointing to last node
	}
}

/* adds a new node at the beginning of the linked list */
void addatbeg ( struct node **q, int num )
{
	struct node *temp ;

	/* add new node */
	temp = ( struct node * ) malloc ( sizeof ( struct node ) ) ;

	temp -> data = num ;
	temp -> link = *q ;
	*q = temp ;
}

/* adds a new node after the specified number of nodes */
void addafter ( struct node *q, int loc, int num )
{
	struct node *temp, *r ;
	int i ;

	temp = q ;
	/* skip to desired portion */
	for ( i = 0 ; i < loc ; i++ )
	{
		temp = temp -> link ;

		/* if end of linked list is encountered */
		if ( temp == NULL )
		{
			printf ( "There are less than %d elements in list\n", loc ) ;
			return ;
		}
	}//After this temp is pointing to loc

	/* insert new node */
	r = ( struct node * ) malloc ( sizeof ( struct node ) ) ;
	r -> data = num ;
	r -> link = temp -> link ;
	temp -> link = r ;
}

/* displays the contents of the linked list */
void display ( struct node *q )
{
	/* traverse the entire linked list */
	while ( q != NULL )
	{
		printf ( "%d ", q -> data ) ;
		q = q -> link ;
	}
	printf ( "\n" ) ;
}

/* counts the number of nodes present in the linked list */
int count ( struct node * q )
{
	int c = 0 ;

	/* traverse the entire linked list */
	while ( q != NULL )
	{
		q = q -> link ;
		c++ ;
	}

	return c ;
}

/* deletes the specified node from the linked list */
void del ( struct node **q, int num )
{
	struct node *old, *temp ;

	temp = *q ;

	while ( temp != NULL )
	{//either temp point to data or both will move
		if ( temp -> data == num )
		{
			/* if node to be deleted is the first node in the linked list */
			if ( temp == *q )
				*q = temp -> link ;
//modify head
			/* deletes the intermediate nodes in the linked list */
			else
				old -> link = temp -> link ;

			/* free the memory occupied by the node */
			free ( temp ) ;
			return ;
		}

		/* traverse the linked list till the last node is reached */
		else
		{
			old = temp ;  /* old points to the previous node */
			temp = temp -> link ;  /* go to the next node */
		 }
	}

	printf ( "Element %d not found\n", num ) ;
}