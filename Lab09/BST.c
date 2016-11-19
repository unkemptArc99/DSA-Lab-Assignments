#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
int index_in=0; 
//Struct representation of tree 
struct node
{
    int key;
    struct node *left, *right;
};
 
struct doubly
{
    int val;
    struct doubly *next,*prev;
};
// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
 
// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
 
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
    printf("entered\n");
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
 
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
 
    /* return the (unchanged) node pointer */
    return node;
}
 
/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->key = temp->key;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

//Code for printing the preorder traversal of the graph
void preorder(struct node* root)
{
    if(root!=NULL)
    {
        printf("%d ",root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

//Code for printing the preorder traversal of the graph
void postorder(struct node* root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->key);
    }
}
//Counting the closest node
int closest_node(struct node *root,int diff,int num,int key)
{
    if(root!=NULL)
    {
        int d=0,k=root->key;
        if(num<k)
        {
            d=k-(num);
            if(diff>d)
            {
                diff=d;
                key=k;
            }            
            key=closest_node(root->left,diff,num,key);
        }
        else if(num>k)
        {
            d=(num)-k;
            if(diff>d)
            {
                diff=d;
                key=k;
            }
            key=closest_node(root->right,diff,num,key);
        }
        else
        {
            diff=0;
            key=k;
        }
        return key;
    }
    else
    {
        return key;
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
void find(struct node *root,int *pre,int *suc,int num)
{
    if(root!=NULL)
    {
        if(root->key==num)
        {
            if(root->left!=NULL)
            {
                struct node *temp=root->left;
                while(temp->right)
                    temp=temp->right;
                *pre=temp->key;
            }
            if(root->right!=NULL)
            {
                struct node *temp=root->right;
                while(temp->left)
                    temp=temp->left;
                *suc=temp->key;
            }
            return;
        }
        else if(root->key>num)
        {
            *suc=root->key;
            find(root->left,pre,suc,num);
        }
        else
        {
            *pre=root->key;
            find(root->right,pre,suc,num);
        }
    }
    else
        return;
}
// Driver Program to test above functions
int main()
{
    struct node *root = NULL;
    int ch,no,height=0,diff,ke,*s,i,pre=-1,suc=-1;
    struct doubly *root1=NULL,*temp,*temp1;
    system("clear");
    printf("Welcome to the Binary Search Tree Simulator\n");
    printf("-------------------------------------------\n");
    while(1)
    {
        printf("\n1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Inorder\n");
        printf("4. Postorder\n");
        printf("5. Preorder\n");
        printf("6. Closest node\n");
        printf("7. Total node\n");
        printf("8. Doubly Linked List\n");
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("Enter the data to enter : ");
                scanf("%d",&no);
                printf("%d",no);
                root=insert(root,no);
                break;
            case 2:
                printf("Enter the number to be deleted");
                scanf("%d",&no);
                root=deleteNode(root,no);
                break;
            case 3:
                inorder(root);
                break;
            case 4:
                postorder(root);
                break;
            case 5:
                preorder(root);
                break;
            case 6:
                printf("Enter the number you want to calculate on : ");
                scanf("%d",&no);
                diff=INT_MAX;
                ke=root->key;
                ke=closest_node(root,diff,no,ke);
                printf("%d",ke);
                break;
            case 7:
                printf("There are %d node(s) in the graph",totalnodes(root));
                break;
            case 8:
                //modifier(root);
                /*no=totalnodes(root);
                s=(int *)malloc(no*sizeof(int));
                inorder_redefined(root,s);
                for(i=0;i<no;++i)
                {
                    if(root1==NULL)
                    {
                        root1=(struct doubly *)malloc(sizeof(struct doubly));
                        root1->val=s[i];
                        root1->prev=NULL;
                        root1->next=NULL;
                    }
                    else
                    {
                        temp1=root1;
                        while(temp1->next!=NULL)
                            temp1=temp1->next;
                        temp=(struct doubly *)malloc(sizeof(struct doubly));
                        temp->val=s[i];
                        temp->next=NULL;
                        temp->prev=temp1;
                        temp1->next=temp;
                    }
                }*/
                break;
            case 9:
                printf("Enter the number : ");
                scanf("%d",&no);
                find(root,&pre,&suc,no);
                if(pre==-1)
                    printf("No predecessor\n");
                else
                    printf("%d is predecessor\n",pre);
                if(suc==-1)
                    printf("No successsor\n");
                else
                    printf("%d is successor\n",suc);
                break;
        }
    }
    return 0;
}
