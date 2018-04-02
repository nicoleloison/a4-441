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
int max_level = 10;

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

/*returns created new node from id # */
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

/*insert a new node temp in the tree at root*/
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

/*returns parent of node from child and root*/
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

/*returns the number of tries from original Xming node
to get to root of three the node */
int tries (int xming, int tries){
    tries ++;
    return tries;
}


/*arr[] array of ids of transmitting nodes, size the number of transmitting nodes
 root the root of tree, child the node we want the parent of*/
int probe(node * root, node * child, int arr[], int size)
{
    node * parent = NULL;
    if (root==NULL || child == NULL)
        return -1;
    
    int collisions =0;
    
    for (int i = 0; i < size; ++i) {
      
        node * temp = search(root, arr[i]);
       // printf("In PROBE: arr: %d , temp: %d\n",arr[i], temp->id);
        if (temp->id == arr[i]){
            
            parent = get_parent_node(root, temp);
            if (parent->id == 0){
                //printf("Got to root from %d\n" ,temp-> id);
                return collisions;
            }
            
            else if (parent && parent->data == 0){
                
                parent->data = 1 ;
                arr[i]=parent->id;
              //  printf("%d:%d -> %d:%d\n",temp-> id,temp->data, parent->id, parent->data);
                //attempt++;
                
                probe(root, parent, arr, size);
            }
            
            else if (parent && parent->data != 0){
                collisions++;
                parent->data = 0;
                printf("Collision on %d at level %d \n",parent->id,parent->level);
                probe(root, temp, arr, size);
                
            }
        }
    }
    return collisions;
    
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

/*return a random int between 0 and n*/
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

/********************************************* main ********************************************/

int main()
{
    int j =1;
    int n = total_nodes(max_level);//test value with 3 levels.
    int bottom = (int) pow(2, max_level);//number of nodes at bottom level
   
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
    
    /*stores the xming nodes in t[] */
    int t[k] ;
    int xming = sizeof(t)/sizeof(int);
    transmitting(root, bottom, t ,k);

    /*calclulate the number of attempts it takes for probes to reach the root without collisions*/
    int collisions=0;
    
    for (int i = 0; i <k; ++i) {
        node * test = search (root, t[i]);
        if (test){
            int at = probe(root, test, t, k);
            collisions = collisions + at;
        }
    }
    
    
    //TODO : 100 tries of that ^
    //get probing from a specific level.
    
  
    //success rate = number of xming nodes /
    int successfull = xming - collisions;
    int attempt = xming + collisions;
    double success = (double) xming * 100/ (double) attempt;
    double avg = (double) attempt / (double) xming;
    double direct_probes = (double) successfull * 100/ (double) xming;
    
    printf("\nTransmitting frames:\t");
   // printf("Number of Attempts: %d \n", attempt);
    printf("Collisions:\t");
    printf("Avg number of tries per frame:\t");
   // printf("Directly Succesfull probes rate is %f percent\n", direct_probes);
    printf("Success rate:\n");
    printf("\t %d\t\t",xming);
    printf(" %d\t\t\t",collisions);
    printf(" %f\t\t",avg);
    printf(" %f\n",success);
   
    t[0] = 0;
    printf("\n --end--\n ");
    return 0;
}
