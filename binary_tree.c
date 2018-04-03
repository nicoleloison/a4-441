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

/** max number of nodes = 2 ^ level TO REMOVE AFTER TEST**/
int max_level = 3;
int start_level = 2;
int scenario = 3;

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

int main(int argc, char* argv[])
{
    /*TO REMOVE AFTER TESTING
     reading arguments from user: ./binary maxlevel tries (start) )
    if (argc!=4)
    {
        printf("Please enter 3 arguments: ./binary max_level, start_level, scenario\n");
        return -1;
    }
    int max_level= (int)argv[1];
    int start_level = (int)argv[2];
    int scenario = (int)argv[3];
    printf("\n\nmax: %d, tries: %d, start:%d\n\n", max_level, start_level, scenario);
    */
    
    int j =1;
    int n = total_nodes(max_level);//number of nodes total in tree (virtual and real)
    int bottom = (int) pow(2, max_level);//number of real nodes (bottom level)
   
    /*create tree and fill it*/
    node *root=NULL,*temp;
    srand(time(NULL));
    
    while(j <= n)
    {
        temp=create(j);
        if(root==NULL)
            root=temp;
        else
            insert(root,temp);
        
        j++;
        
    }
    
    /*for statistics*/
    int sum_successfull=0;
    int sum_attempt = 0;
    double sum_avg =0.0;
    double direct_probes = 0.0;
    double sum_success =0.0;
   
    int count =0;
    do{
        printf("\nCOUNT:%d SCENARIO: %d\n",count, scenario );
        
        /*ready = the random number of node transmitting*/
        int ready = (int)(rand()) %  (int)(pow(2, max_level)+1);
        
        while(ready == 0){
            /*in case we end up with no transmitting nodes*/
            ready = (int)(rand()) %  (int)(pow(2, max_level)+1);
            /*k = random id of nodes transmiting*/
        }
        
        /*stores the xming nodes in t[]*/
        int t[ready] ;
        int xming = sizeof(t)/sizeof(int);
        transmitting(root, bottom, t ,ready);
        
        /* calclulate the number of attempts it takes for probes to reach
         the root including collisions */
        int collisions=0;
        for (int i = 0; i <ready; ++i) {
            node * test = search (root, t[i]);
            if (test){
                int at = probe(root, test, t, ready);
                collisions = collisions + at;
            }
        }
        
        int successfull = xming - collisions;
        int attempt = xming + collisions;
        double avg = (double) attempt / (double) xming;
        double direct_probes = (double) successfull * 100/ (double) xming;
        double success = (double) xming * 100/ (double) attempt;
        
        
        
        
        
        
        
        
        
        
        t[0] = 0;
        
        count ++;
    }while(count < scenario);
    
    
    
    
   /*
    printf("\nReady stations:\t\t");
   
    printf("Collisions:\t");
    printf("Avg rounds per stations:\t");
    printf("Average case performance:\n");
    printf("\t %d\t\t",xming);
    printf("  %d\t\t\t",collisions);
    printf(" %f\t\t",avg);
    printf(" %f\n",success);

    printf("Number of Attempts: %d \n", attempt);
    printf("Directly Succesfull probes rate is %f percent\n", direct_probes);*/

    printf("\n --end--\n ");
    return 0;
}
