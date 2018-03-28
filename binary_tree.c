/*
 GARANCE NICOLE LOISON
 ASSIGNMENT 4 - CPSC 441
 BINARY TREE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <errno.h>

/** max number of nodes = 2 ^ level **/
int max_level = 3;

/** helper functions **/
unsigned int int_to_binary(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_binary(k / 2)));
}

unsigned int level_from_id(unsigned int node_id){
    int level = log10(node_id) / log10(2);
    return level;
}

/* tree structure */
typedef struct tree
{
    int id, level;
    int data;
    struct tree *left;
    struct tree *right;
}node;

/* node struc and helper functions */
node *create();
void insert(node *,node *);
void preorder(node *);

struct node
{
    int id, data, level;
    struct node *left;
    struct node *right;
};

node *create(int id)
{
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->id = id-1;
    temp->data = 0;
   //temp->id  = int_to_binary(id-1);
    temp->level  = level_from_id(id);
    temp->left=temp->right=NULL;
    //printf("created node with id:%d at level:%d \n", temp->id, temp->level);
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
/* recursive traversal of tree and
 printing of nodes id in tree increasing order*/
void preorder(node *root)
{
    if(root!=NULL)
    {
        printf("id: %d - data: %d - level: %d\n",root->id, root->data, root->level);
        preorder(root->left);
        preorder(root->right);
    }
    
}

/* recursive traversal of tree and
 printing of nodesin bottom view*/
void bottom_view(node *root)
{
   // int * bot_ids;
    int i=0;
    if(root!=NULL)
    {
        if ((root->level) == max_level && (root->data)==1){
            printf("%d - ",root->id);
            //bot_ids[i]=root->id;
        }
        bottom_view(root->left);
        bottom_view(root->right);
    }
  //  return bot_ids;
}


/* recursive traversal of tree and
 printing of nodes id in tree increasing order*/
node* search(node *root, int key){
    node* found = NULL;
    
    if(root == NULL)
        return NULL;
    
    
    if(root->id== key)
        return root;
    
    found = search(root->left, key);
    if (found)
        return found;
    
    found = search(root->right, key);
    if (found){
        return found;
    }
    
    
    return NULL;
}

/* recursive traversal of tree and
 printing of nodes id in tree increasing order*/
node* check(node *root){

    
    return NULL;
}
/* returns the factorial of int n
 we want 2^level nodes at the bottom level
 total # of nodes = sum of nodes at each level*/
int total_nodes(int n){
    int total = 0;
    do{
        total = total + pow(2, n);
        n --;
    }while(n>=0);
    
    return total;
}

int randRange(int n){
    int limit , r;
    limit = RAND_MAX - (RAND_MAX % n);

   // r = (rand() % (pow(2, max_level) + 1 ))
    while((r = rand()) >= limit);
    r = r % n;
    return r+n;
}


/*get a random number of nodes with random_int
 and returns each randomly selected with random_int*/
node * transmitting(node * root,  int n){
    node * temp;
    node * transmitting_nodes;
    int k = randRange(n)+1;
   
    printf("transmitting nodes:\n ");
    for (int i =0 ; i< k; i++){
        int key =randRange(n)+1;
        node * found = search(root, key);
        
        if (found !=NULL){
            found->data = 1;
            printf("%d - ",found->id);
        }
    }
  
    return transmitting_nodes;
}

/*returns all nodes with level = key
node * starting(node * root,  int bottom){
    node * temp;
    node * probers;
    
    printf("\ndata = 1 nodes:\n ");
    for (int i =0 ; i< bottom; i++){
        node * found = probe(root);
        
        if (found !=NULL){
            //found->data = 1;
            printf("%d - ",found->id);
        }
    }
    
    return probers;
}

/****************************** main ***************************/
int main()
{
    int j =1;
    int n = total_nodes(max_level);//test value with 3 levels.
    int bottom = (int) pow(2, max_level);
    /*create root*/
    node *root=NULL,*temp, *rando;
    
    while(j <= n)
    {
        temp=create(j);
        if(root==NULL)
            root=temp;
        else
            insert(root,temp);
        
        j++;
        
    }
    
    srand(time(NULL));
   // transmitting(root, n);
    
    node * seekers = transmitting(root, bottom);
   // int * bottom_ids =
    printf("\nxming ids:\n");
    bottom_view(root);
    
    //printf("\n All Nodes: \n");
    //preorder(root);
   // printf("\n Bottom View: \n");
    //bottom_view(root);
    printf("\n --end--\n ");
    return 0;
}
