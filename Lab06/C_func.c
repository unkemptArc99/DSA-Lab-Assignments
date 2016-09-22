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
		temp -> random = NULL;
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
		r -> random = NULL;
		temp -> link = r ;//temp is pointing to last node
	}
}

//function for the input of random pointers
void randominit(struct node **q,int count)
{
	struct node *temp;				//Main loop pointer
	temp=*q;
	while(temp!=NULL)
	{
		int num;
		printf("Enter the random node to assign (0-indexed) (less than %d [this is the size of the current list]) : ",count);
		scanf("%d",&num);
		int i;
		struct node *temp1;
		temp1=*q;
		int flag=0;
		while(temp1!=NULL)
		{
			if(temp1->data==num)
			{
				temp->random=temp1;
				flag=1;
				break;
			}
			temp1=temp1->link;
		}
		temp=temp->link;
	}
}

void display ( struct node *q )
{
	/* traverse the entire linked list */
	printf("%16s %16s %16s %16s\n","Value","Address","Next Pointer","Random Pointer");
	while ( q != NULL )
	{
		printf ( "%16d %16p %16p %16p\n", q -> data, q, q->link, q->random ) ;
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

struct node *deepCopy(struct node **q)
{
	struct node *original,*copy;
	original=*q;
	while(original!=NULL)
	{
		struct node *temp;
		temp=(struct node *)malloc(sizeof(struct node));
		temp->data=original->data;
		temp->link=original->link;
		temp->random=original->random;
		original->link=temp;
		original=temp->link;
	}
	original=*q;
	copy=original->link;
	struct node *temp=copy;
	while(original->link!=NULL && copy->link!=NULL)
	{
		original->link=original->link->link;
		copy->link=copy->link->link;
		original=original->link;
		copy=copy->link;
	}
	original=NULL;
	return temp;
}