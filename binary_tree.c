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

int max_level = 4;


typedef struct tree
{
    int id;
    struct tree *left;
    struct tree *right;
}node;

node *create();
void insert(node *,node *);
void preorder(node *);

unsigned int int_to_binary(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_binary(k / 2)));
}

int node_level(unsigned int k) {
    int level = pow(2, k) - 1 ;
    printf("node id is:\t%d, level:\t%d\n", k,  level);
    return level;
}

unsigned int get_level(unsigned int node_id){
    int level = log10(node_id) / log10(2);
    printf("node id is:\t%d, level:\t%d\n", node_id, level);
    return level;
}

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
    temp->id  = id;
    temp->left=temp->right=NULL;
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

void preorder(node *root)
{
    if(root!=NULL)
    {
        printf("%d ",root->id);
        preorder(root->left);
        preorder(root->right);
    }
}



int main()
{
    unsigned long long factorial = 1;
    // show error if the user enters a negative integer
    if (max_level < 0)
        printf("Error! max level of a negative number doesn't exist.");
    
    else
    {
        for(int i=1; i<=max_level; ++i)
        {
            factorial *= i;              // factorial = factorial*i;
        }
        printf("Factorial of %d = %llu\n", max_level, factorial);
    }
    
    int j =1;
    /*create root*/
    node *root=NULL,*temp;
    
    while(j < factorial)
    {
        temp=create(j);
        if(root==NULL)
            root=temp;
        else
            insert(root,temp);
        
        get_level(j);
        j ++;
        
    }
    
    printf("\n Preorder Traversal: ");
    preorder(root);
    printf("\n --end--\n ");
    return 0;
}
