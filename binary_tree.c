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
    int id, level, binary;
    int data;
    struct tree *left;
    struct tree *right;
}node;

/* node struc and helper functions */
struct node
{
    int id, data, level, binary;
    struct node *left;
    struct node *right;
};

node *create();
void insert(node *,node *);
void preorder(node *);

node *create(int id)
{
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->id = id-1;
    temp->data = 0;
    temp->binary  = int_to_binary(id-1);
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
 printing of nodes in bottom view that are transmitting*/
void bottom_view(node *root)
{
    if(root!=NULL)
    {
        int i =0;
        if ((root->level) == max_level && (root->data)==1){
            printf("%d - ",root->id);
            i++;
        }
        bottom_view(root->left);
        bottom_view(root->right);
    }
    
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
    if (found)
        return found;
    
    return NULL;
}

node * get_parent_node(node * root, node * child){
    node * parent = NULL;
    
    if(root == NULL)
        return NULL;
    
    printf("Looking from %d at node %d \n", root->id, child->id);
    
    int parity = child->id % 2;
    int parentID;
    
    if (parity !=0){
        parentID = child->id -1;
        printf("parent ID: %d \n",parentID);
        parent = search(root, parentID);
        if (parent)
            return parent;
        
    }
    
    else{
        parentID = child->id -2;
        printf("parent ID: %d \n",parentID);
        parent = search(root, parentID);
        if (parent)
            return parent;
    }
    
    return NULL;
}
void probe(node * root, node * child,int arr[], int size)
{
    node * temp = NULL;
    if (root==NULL)
        return;
    
    temp = root;
    
    for (int i = 0; i < size; ++i) {
        
        if (temp->binary == arr[i]){
            temp = ;
            if (temp!=NULL){
                // printf("temp id %d \n", temp-> id);
            }
            
            //printf("parent %d with %d\n", temp->id, temp->level);
        }
    }
    
    //if (root->data == 1)
    // printf("parent: %d ", root->binary);
    
    
    post_order(root->left, arr, size);
    post_order(root->right, arr, size);//printPostorder(root->right);
    
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
    while((r = rand()) >= limit);
    r = r % n;
    return r+n;
}


/*get a random number of nodes with random_int
 and returns each randomly selected with random_int*/
node * transmitting(node * root,  int n, int arr[], int k){
    node * transmitting_nodes;
    int i =0;
    while (i < k){
        int key =randRange(n)+1;
        node * found = search(root, key);
        if (found != NULL){
            printf("%d ", found->id);
            found->data = 1;
            arr[i]=found->binary;
            i ++;
        }
    }
     printf("\n");
  
    return transmitting_nodes;
}

/********************************************************/
int getAverage(int arr[], int size) {
    
    int i;
    int avg;
    int sum = 0;
    
    for (i = 0; i < size; ++i) {
        sum += arr[i];
    }
    
    avg = (int) (sum / size);
    
    return avg;
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
    int k = (int)(rand()) %  (int)(pow(2, max_level)+1);
   
    while(k == 0){
        /*in case we end up with no transmitting nodes*/
        k = (int)(rand()) %  (int)(pow(2, max_level)+1);
    }
    int t[k] ;
    for (int i = 0; i <k; ++i) {
        t[i]=0;
    }
    int l = sizeof(t)/sizeof(int);
    transmitting(root, bottom, t ,k);
    t[l]=0;
  
    //printf("Xming ids:\n");
    bottom_view(root);
    printf(" \n");
    
    node * test = search(root, 8);
    node * node_six = get_parent_node(root, test);
    printf("should be 6:%d, 0: %d, 2:%d\n", node_six->id, node_six->data, node_six->level);

    //printf("\n All Nodes: \n");
    //preorder(root);
   // printf("\n Bottom View: \n");
    //bottom_view(root);
    t[0] = 0;
    printf("\n --end--\n ");
    return 0;
}
