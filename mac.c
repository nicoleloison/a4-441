/*
 GARANCE NICOLE LOISON
 ASSIGNMENT 4 - CPSC 441
 ADAPTIVE TREE WALK PROTOCOL
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <errno.h>

/*FOR EASY TESTING
 max number of nodes = 2 ^ level
int max_level = 10;
int start_level = 4;
int scenario = 1000;*/

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
void bottom_view(node *root, int max_level)
{
    if(root!=NULL)
    {
        int i =0;
        if ((root->level) == max_level && (root->data)==1){
            i++;
        }
        bottom_view(root->left, max_level);
        bottom_view(root->right, max_level);
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

/*arr[] array of ids of transmitting nodes, size the number of transmitting nodes
 root the root of tree, child the node we want the parent of*/
int probe(node * root, node * child, int arr[], int size, int start, int collisions)
{
    node * parent = NULL;
    if (root==NULL || child == NULL)
        return -1;
    
    if (start == 0){
        return 0;
    }
    
    for (int i = 0; i < size; ++i) {
      
        node * temp = search(root, arr[i]);
       // printf("In PROBE: arr: %d , temp: %d\n",arr[i], temp->id);
        if (temp->id == arr[i]){
            parent = get_parent_node(root, temp);
            if (parent->id == 0){
                //printf("Got to root from %d\n" ,temp-> id);
                //return collisions;
                return 0;
            }
            
            else if (parent && parent->data == 0){
                parent->data = 1 ;
                arr[i]=parent->id;
                probe(root, parent, arr, size, start, collisions);
            }
            
            else if (parent && parent->data != 0){
                ++collisions;
                parent->data = 0;
               // printf("col: %d ",collisions);
                probe(root, temp, arr, size,start, collisions);
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
int random_generator(int n){
    int limit , r;
    limit = RAND_MAX - (RAND_MAX % n);
    while((r = rand()) >= limit);
    r = r % n;
    return r+n;
}


/*get a random number of nodes with random_int
 and returns each randomly selected with random_int*/
node * transmitting(node * root,  int start, int arr[], int k){
    node * transmitting_nodes;
    int i =0;
    
    if (start == 0){
        return root;
    }
  
    while (i < k){
        int key =random_generator(start)+1;
        node * found = search(root, key);
        if (found != NULL){
            found->data = 1;
            arr[i]=found->id;
            //printf("%d - ", arr[i]);
            i ++;
        }
    }
    return transmitting_nodes;
}

/********************************************* main ********************************************/

int main(int argc, char* argv[])
{
    
    /* reading arguments from user: ./binary maxlevel tries (start) )*/
    if (argc!=4)
    {
        printf("Please enter 3 arguments: ./binary max_level(1->10) start_level(1->10) scenario(>0)\n");
        return -1;
    }
    int max_level= atoi(argv[1]);
    int start_level = atoi(argv[2]);
    int scenario = atoi(argv[3]);
    
    if (max_level>10 || max_level<0 || start_level>max_level || start_level<0 || scenario<0){
        printf("Please enter input such that:\n"
               "0 < max level < 10\n"
               "0 < start level < 10\n"
               "scenario > 0/n");
        return -1;
    }
    
    int j =1;
    int n = total_nodes(max_level);//number of nodes total in tree (virtual and real)
    int bottom = (int) pow(2, max_level);//number of real nodes (bottom level)
    
    printf("\nNumber of real nodes:\t Number of Scenarios:\t Starting Level:\t\n");
    printf("\t%d \t\t\t %d \t\t\t %d \t\n",bottom,scenario,start_level );
    
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
    double total_probes = 0.0;
    double failure_rate =0.0;
    double totxming =0.0;
    double collision_per_test=0.0;
    
    int count =0;
    do{
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
        
        /*define the transmitting nodes from user input*/
        transmitting(root, start_level, t, ready);
        
        /* calclulate the number of attempts it takes for probes to reach
         the root including collisions */
        int collisions=0, sum=0 , tot=0;
        double failure=0.0;
        for (int i = 0; i <ready; ++i) {
            node * test = search (root, t[i]);
            if (test){
                sum += probe(root, test, t, ready, start_level, 0);
                collisions = collisions+sum;
            }
        }
        tot=collisions+xming;
        failure  = (double) collisions*100/tot;
       // printf("\nfailure: %f\tcol: %d\txming: %d\ttot:%d\n",failure, collisions , xming, tot);
    
        totxming += (double)xming;
        total_probes += (double)tot;
        
        collision_per_test += (double) collisions * (start_level);
        failure_rate += (double) failure;

        t[0] = 0;
        count ++;
    }while(count < scenario);
    
    
    
    /*compute avg of stats*/
    totxming = totxming /scenario;
    collision_per_test = collision_per_test/scenario;
    total_probes = total_probes /scenario;
    //failure_rate = 100 - (failure_rate/scenario) ;
    
    failure_rate = collision_per_test / (total_probes);
    double success_rate = 100 - failure_rate;

    
    printf("\nAvg number of ready stations:\t%f\n", totxming);
    printf("Avg total probes:\t\t%f\n", total_probes);
    printf("Avg collisions per test:\t%f\n", collision_per_test);
    printf("\nFailure rate:\t%f\tAvg Test Performance:\t%f\n\n\n", failure_rate, success_rate);

    return 0;
}
