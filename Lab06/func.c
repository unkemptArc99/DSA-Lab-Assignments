randomlistnode *copyRandomList(randomlistnode *q)
{
	randomlistnode *original,*copy;
	original=q;
	while(original!=NULL)
	{
		randomlistnode *temp;
		temp=(randomlistnode *)malloc(sizeof(randomlistnode));
		temp->label=original->label;
		temp->next=original->next;
		temp->random=original->random;
		original->next=temp;
		original=temp->next;
	}
	original=q;
	copy=original->next;
	randomlistnode *temp=copy;
	while(original->next!=NULL && copy->next!=NULL)
	{
		original->next=original->next->next;
		copy->next=copy->next->next;
		original=original->next;
		copy=copy->next;
	}
	original->next=NULL;
	return temp;
}