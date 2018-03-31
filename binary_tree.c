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
    
    if(root->id== key){
      //  printf("in search found id: %d\n", root->id);
       return root;
    }
    
    
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
    
    if(root==NULL || child == NULL)
        return NULL;
    
    int parity = child->id % 2;
    int parentID;
    
    if (parity !=0){
        parentID = child->id/2;
    //    printf("parent ID: %d \n",parentID);
        parent = search(root, parentID);
        if (parent)
            return parent;
        
    }
    
    else{
        parentID = child->id/2 -1;
       // printf("parent ID: %d \n",parentID);
        parent = search(root, parentID);
        if (parent)
            return parent;
    }
    
    return NULL;
}

/*arr[] array of ids of transmitting nodes, size the number of transmitting nodes
 root the root of tree, child the node we want the parent of*/
void probe(node * root, node * child, int arr[], int size)
{
   
    node * parent = NULL;
    
    if (root==NULL || child == NULL)
        return;
    
   // printf("In PROBE: root %d, temp: %d , child: %d\n",root->id,temp->id, child->id);
    
    for (int i = 0; i < size; ++i) {
        node * temp = search(root, arr[i]);
        //printf("In PROBE: i: %d, arr: %d , temp: %d\n",i,arr[i], temp->id);
        if (temp->id == arr[i]){
           // printf("Node %d in Xming \n", temp->id);
            parent = get_parent_node(root, temp);
            if (parent && parent->data == 0){
                parent->data = 1;
                printf("%d parent of %d is now : %d\n",parent->id, temp-> id, parent->data);
            }
            else if (parent && parent->data != 0){
                printf("Parent %d is already taken : COLLISION ?\n",parent->id);
            }
        }
    }
    
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
            arr[i]=found->id;
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
    /*k = the random number of node transmitting*/
    srand(time(NULL));
    int k = (int)(rand()) %  (int)(pow(2, max_level)+1);
   
    while(k == 0){
        /*in case we end up with no transmitting nodes*/
        k = (int)(rand()) %  (int)(pow(2, max_level)+1);
        /*k = random id of nodes transmiting*/
    }
    int t[k] ;
    for (int i = 0; i <k; ++i) {
        t[i]=0;
    }
    int l = sizeof(t)/sizeof(int);
    transmitting(root, bottom, t ,k);
    t[l]=0;
  
    //printf("Xming ids:\n");
   // bottom_view(root);
   // printf(" \n");
    
    for (int i = 0; i <k; ++i) {
        node * test = search (root, t[i]);
        if (test){
           // printf("child:%d, root:%d\n", test->id, root->id );
            probe(root, test, t, k);
        }
        
    }
    /*
    node * node_six = search(root, 6);
    node * node_four = get_parent_node(root, node_six);
    printf("should be 4:%d, 0: %d, 2:%d\n", node_four->id, node_four->data, node_four->level);
     */
    
    //printf("\n All Nodes: \n");
    //preorder(root);
   // printf("\n Bottom View: \n");
    //bottom_view(root);
    t[0] = 0;
    printf("\n --end--\n ");
    return 0;
}
