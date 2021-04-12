#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#define global_space 5
#ifdef __linux__
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#else
#define ANSI_COLOR_RED     ""
#define ANSI_COLOR_RESET   ""
#endif
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
tree_t* new_tree();
node_t* search(node_t* head,int x);
void insert(tree_t* T,int x);
void print_tree(node_t* root, int i,int tar);

int cmd_parse(char* cmd);


int main(){
tree_t* T=new_tree();
char cmd[10];
int tmp;
while(1){
scanf("%s",cmd);
if(cmd[0]=='q')
break;
else{
scanf("%d",&tmp);
int c=cmd_parse(cmd);
switch (c)
    {
        case 6:
            printf("Insert %d into tree\n",tmp);
            insert(T,tmp);
            print_tree(T->root,0,tmp);
        break;
        /*case i:
            insert(T,tmp);
        break;
        case i:
            insert(T,tmp);
        break;
        case i:
            insert(T,tmp);
        break;
        case i:
            insert(T,tmp);*/
        break;
    default:
        printf("Invalid command, type help to see available operations\n");
        break;
    }

}

}

insert(T,30);
insert(T,45);
insert(T,18);
insert(T,25);
insert(T,10);
//print_tree(T->root,0,10);
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

tree_t* new_tree(){
    tree_t* T = malloc(sizeof(tree_t));
    if(!T)
    return T;
    T->root=NULL;
    return T;
}

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

void print_tab(int i){
    for(int j = 0;j<i;j++)
    printf("|\t");
}
void print_tree(node_t* root, int i,int tar){
    if(root==NULL)
    return;
    print_tree(root->right,i+1,tar);
    if(i!=0){
        print_tab(i-1);
            if(root->key==tar)
            printf("|-------"ANSI_COLOR_RED"%d"ANSI_COLOR_RESET"\n",root->key);
            else
            printf("|-------%d\n",root->key);
    }else{
            if(root->key==tar)
            printf(ANSI_COLOR_RED"%d"ANSI_COLOR_RESET"\n",root->key);
            else
            printf("%d\n",root->key);
    }
    print_tree(root->left,i+1,tar);
}
node_t* parent(tree_t* T,node_t* tar){
    node_t* head=T->root;
    if(head==tar)
    return NULL;
    while(head){
        if(head->left==tar||head->right==tar)
        return head;
        else if (head->key>tar->key)
        head=head->left;
        else
        head=head->right;
    }
    return NULL;
}
/*
void transp(tree_t* T,node_t* u,node_t* v){
    if()
}*/
int cmd_parse(char* cmd){
    printf("%s\n",cmd);
    if(strcmp(cmd,"i")==0)
        return 6;
}

