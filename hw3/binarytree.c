#include<stdio.h>
#include<stdlib.h> 
#define global_space 5
struct node
{
    struct node* left;
    struct node* right;
    int key;
    //int times=0;
};
typedef struct node node_t;
struct tree{
    node_t* root;
};

typedef struct tree tree_t;
node_t* new_node(int k);
node_t* search(node_t* head,int x){
while(head!=NULL && head->key!=x){
    if(head->key>x)
    head=head->left;
    else
    head=head->right;
}
return head;
}

void insert(tree_t* T,int x){
    node_t* head=T->root;
    node_t* ins=new_node(x);
    if(!head){
    T->root=ins;
    return;
    }
    node_t* tmp=NULL;
    while(head){
        tmp = head;
        if(x<head->key)
        head=head->left;
        else
        head=head->right;
    }
    if(tmp->key>x)
    tmp->left=ins;
    else
    tmp->right=ins;
}

void print_space(int i){
    for(int j = 0;j<i;j++)
    printf(" ");
}


void print_tree(node_t* root, int i){
    if(root==NULL)
    return;
    i++;
    print_tree(root->right,i);
    printf("\n");
    print_space((i*global_space));
    printf("%d\n",root->key);
    print_tree(root->left,i);
}


tree_t* new_tree(){
    tree_t* T = malloc(sizeof(tree_t));
    if(!T)
    return T;
    T->root=NULL;
    return T;
}



int main(){
tree_t* T=new_tree();
insert(T,30);
insert(T,45);
insert(T,18);
insert(T,25);
insert(T,10);
print_tree(T->root,1);
}

node_t* new_node(int k){
    node_t* n = malloc(sizeof(node_t));
    if(!n)
        return n;
    n->left=NULL;
    n->right=NULL;
    n->key=k;
    return n;
}