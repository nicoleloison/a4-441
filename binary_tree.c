/*
 GARANCE NICOLE LOISON
 ASSIGNMENT 4 - CPSC 441
 BINARY TREE
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <string.h>

#include <math.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <strings.h>
#include <netdb.h>
#include <stdbool.h>
/** max number of nodes = 2 ^ level **/
int max_level = 3;


unsigned int int_to_binary(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_binary(k / 2)));
}
/** helper functions **/
unsigned int get_level(unsigned int node_id){
    int level = log10(node_id) / log10(2);
    printf("node level:\t%d\n", level);
    return level;
}

/* tree structure */
typedef struct tree
{
    int id;
    struct tree *left;
    struct tree *right;
}node;

/* node struc and helper functions */
node *create();
void insert(node *,node *);
void preorder(node *);
struct node
{
    int id;
    int data;
    struct node *left;
    struct node *right;
};

node *create(int id)
{
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->id  = id-1;
    temp->left=temp->right=NULL;
    printf("created node with id:%d\t", temp->id);
    return temp;
}

void insert(node *root,node *temp)
{
    if(temp->id<root->id)
    {
        if(root->left!=NULL)
            insert(root->left,temp);
        else
            root->left=temp;
    }
    
    if(temp->id>root->id)
    {
        if(root->right!=NULL)
            insert(root->right,temp);
        else
            root->right=temp;
    }
}
/* recursive printing of nodes in tree increasing order*/
void preorder(node *root)
{
    if(root!=NULL)
    {
        printf("%d ",root->id);
        preorder(root->left);
        preorder(root->right);
    }
}


/****************** main ******************/
int main()
{
    int n = pow(2, max_level);
    int j =1;
    /*create root*/
    node *root=NULL,*temp;
    
    do
    {
        temp=create(j);
        if(root==NULL)
            root=temp;
        else
            insert(root,temp);
        
        get_level(j);
        j++;
        
    }while(j < n);
    
    printf("\n Preorder Traversal: ");
    preorder(root);
    printf("\n --end--\n ");
    return 0;
}
