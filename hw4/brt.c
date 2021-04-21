#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<stdbool.h>
//#define global_space 5
#ifdef __linux__
#define ANSI_COLOR_BLUE    "\x1b[36m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#else
#define ANSI_COLOR_BLUE    ""
#define ANSI_COLOR_RED     ""
#define ANSI_COLOR_RESET   ""
#endif
#define RED true
#define BLK false
#define INFO \
"Available commands:\n"\
ANSI_COLOR_RED"i    {int}"ANSI_COLOR_RESET" - " ANSI_COLOR_BLUE"Insert node with key {int} into tree"ANSI_COLOR_RESET"\n"\
ANSI_COLOR_RED"sel  {int}"ANSI_COLOR_RESET" - " ANSI_COLOR_BLUE"Select {int}-th smallest key from tree"ANSI_COLOR_RESET"\n"\
ANSI_COLOR_RED"rank {int}"ANSI_COLOR_RESET" - " ANSI_COLOR_BLUE"Get the rank of {int}"ANSI_COLOR_RESET"\n"\
ANSI_COLOR_RED"graph     "ANSI_COLOR_RESET" - " ANSI_COLOR_BLUE"Print the tree in 2-D graph"ANSI_COLOR_RESET"\n"\
ANSI_COLOR_RED"help      "ANSI_COLOR_RESET" - " ANSI_COLOR_BLUE"Print the help"ANSI_COLOR_RESET"\n"\
ANSI_COLOR_RED"pr        "ANSI_COLOR_RESET" - " ANSI_COLOR_BLUE"Print the tree in Pre-order traversal"ANSI_COLOR_RESET"\n"\
ANSI_COLOR_RED"q         "ANSI_COLOR_RESET" - " ANSI_COLOR_BLUE"exit"ANSI_COLOR_RESET"\n"\

struct node
{
    struct node* left;
    struct node* right;
    int key;
    int cnt;
    bool color;
    //int times=0;
};
typedef struct node node_t;
struct tree{
    node_t* root;
    node_t* nil;
};
typedef struct tree tree_t;
node_t* new_node(tree_t* T,int k);
tree_t* new_tree();
node_t* search(tree_t* T,node_t* head,int x);
void print_tree(tree_t* T,node_t* root, int i,int tar);
node_t* parent(tree_t* T,node_t* tar);
void l_rotate(tree_t* T,node_t* x);
void r_rotate(tree_t* T,node_t* x);
void rb_insert(tree_t* T,node_t* z);
node_t* sel(tree_t* T,node_t* x,int i);
int rank(tree_t* T,node_t* x);
//void mod_parent(tree_t* T,node_t* tar,node_t* post);
void pre_order(tree_t* T,node_t* t);

int cmd_parse(char* cmd);
void FIX(tree_t* T,node_t* z);
int main(){
tree_t* T=new_tree();
char cmd[10];
int tmp;
node_t* t;
printf(INFO);
while(1){
scanf("%s",cmd);
cmd[9]='\0';
if(cmd[0]=='q')
break;
else{
int c=cmd_parse(cmd);
switch (c)
    {   
        case 1:
            scanf("%d",&tmp);
            printf("Insert %d into tree\n",tmp);
            t=new_node(T,tmp);
            rb_insert(T,t);
            //print_tree(T,T->root,0,t->key);
        break;
        case 2:
            scanf("%d",&tmp);
            printf("Select %d-th smallest key from tree\n",tmp);
            t=sel(T,T->root,tmp);
            if(t!=T->nil){
            if(t->color)
            printf(ANSI_COLOR_RED"%d red %d"ANSI_COLOR_RESET"\n",t->key,t->cnt);
            else
            printf(ANSI_COLOR_BLUE"%d black %d"ANSI_COLOR_RESET"\n",t->key,t->cnt);
            }
            //print_tree(T,T->root,0,t->key);
        break;
        case 3:
            scanf("%d",&tmp);
            printf("Get the rank of %d\n",tmp);
            t=search(T,T->root,tmp);
            if(t){
                tmp = rank(T,t);
                printf("%d\n",tmp);
                tmp=t->key;
            }
            else
            printf("%d WAS NOT IN TREE\n",tmp);
        break;
        case 4:
            pre_order(T,T->root);
        break;
        case 5:
            print_tree(T,T->root,0,tmp);
        break;
        case 6:
            printf(INFO);
        break;   
    default:
        printf("Invalid command, type help to see available operations\n");
        break;
    }

}

}

}

node_t* new_node(tree_t* T,int k){
    node_t* n = malloc(sizeof(node_t));
    if(!n)
        return T->nil;
    n->left=T->nil;
    n->right=T->nil;
    n->key=k;
    n->cnt=1;
    n->color=BLK;
    return n;
}

tree_t* new_tree(){
    tree_t* T = malloc(sizeof(tree_t));
    if(!T)
    return T;
    T->nil=malloc(sizeof(node_t));
    T->nil->color=BLK;
    T->nil->cnt=0;
    T->nil->left=T->nil;
    T->nil->right=T->nil;
    T->root=T->nil;
    return T;
}

node_t* search(tree_t* T,node_t* head,int x){
while(head!=T->nil && head->key!=x){
    if(head->key>x)
    head=head->left;
    else
    head=head->right;
}
return head;
}

void rb_insert(tree_t* T,node_t* z){
    node_t* y = T->nil;
    node_t* x = T->root;
    while(x!=T->nil){
        y=x;
        x->cnt++;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    if(y==T->nil)
        T->root=z;
    else if (z->key<y->key)
        y->left=z;
    else
        y->right=z;
    z->left=T->nil;
    z->right=T->nil;
    z->color=RED;
    FIX(T,z);
}

void FIX(tree_t* T,node_t* z){
    while(parent(T,z)->color==RED){
        if(parent(T,z)==parent(T,parent(T,z))->left){
            node_t* y = parent(T,parent(T,z))->right;
            if(y->color==RED){
                parent(T,z)->color=BLK;
                y->color=BLK;
                parent(T,parent(T,z))->color=RED;
                z=parent(T,parent(T,z));
            }
            else {
            if (z==parent(T,z)->right){
                z=parent(T,z);
                l_rotate(T,z);
            }
            parent(T,z)->color=BLK;
            parent(T,parent(T,z))->color=RED;
            r_rotate(T,parent(T,parent(T,z)));
            }
        }else{
            node_t* y = parent(T,parent(T,z))->left;
            if(y->color==RED){
                parent(T,z)->color=BLK;
                y->color=BLK;
                parent(T,parent(T,z))->color=RED;
                z=parent(T,parent(T,z));
            }
            else {
            if (z==parent(T,z)->left){
                z=parent(T,z);
                r_rotate(T,z);
            }
            parent(T,z)->color=BLK;
            parent(T,parent(T,z))->color=RED;
            l_rotate(T,parent(T,parent(T,z)));
            }
        }
    }
T->root->color=BLK;
T->nil->color=BLK;
}



void print_tab(int i){
    for(int j = 0;j<i;j++)
    printf("|\t");
}
void print_tree(tree_t* T,node_t* root, int i,int tar){
    if(root==T->nil){
        /*
        if(i!=0)
        print_tab(i-1);
        printf("|======="ANSI_COLOR_BLUE"N"ANSI_COLOR_RESET"\n");
        */
    return;
    }
    print_tree(T,root->right,i+1,tar);
    if(i!=0){
        print_tab(i-1);
            if(root->key==tar){
                if(root->color==RED)
                printf("|======="ANSI_COLOR_RED"{*%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
                else
                printf("|======="ANSI_COLOR_BLUE"{%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            }
            else if(root->color==RED)
            printf("|======="ANSI_COLOR_RED"*%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            else 
            printf("|======="ANSI_COLOR_BLUE"%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            
    }else{
            if(root->key==tar){
                if(root->color==RED)
                printf(ANSI_COLOR_RED"{*%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
                else
                printf(ANSI_COLOR_BLUE"{%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            }
            else if(root->color==RED)
            printf(ANSI_COLOR_RED"*%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            else 
            printf(ANSI_COLOR_BLUE"%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
    }
    print_tree(T,root->left,i+1,tar);
}

node_t* parent(tree_t* T,node_t* tar){
    node_t* head=T->root;
    if(head==tar)
    return T->nil;
    while(head!=T->nil){
        if(head->left==tar||head->right==tar)
        return head;
        else if (head->key>tar->key)
        head=head->left;
        else
        head=head->right;
    }
    return T->nil;
}


void l_rotate(tree_t* T,node_t* x){
    printf("Call l_rotate at %d\n",x->key);
    node_t* y=x->right;
    x->right=y->left;
    if(parent(T,x)==T->nil)
        T->root=y;
    else if(x==parent(T,x)->left)
        parent(T,x)->left=y;
    else
        parent(T,x)->right=y;
    y->left=x;
    y->cnt=x->cnt;
    x->cnt=x->left->cnt+x->right->cnt+1;
}


void r_rotate(tree_t* T,node_t* x){
    printf("Call r_rotate at %d\n",x->key);
    node_t* y=x->left;
    x->left=y->right;
    if(parent(T,x)==T->nil)
        T->root=y;
    else if(x==parent(T,x)->right)
        parent(T,x)->right=y;
    else
        parent(T,x)->left=y;
    y->right=x;
    x->cnt=y->cnt;
    y->cnt=y->left->cnt+y->right->cnt+1;
}

node_t* sel(tree_t* T,node_t* x,int i){
    if(x==T->nil){
    printf("Key not found\n");
    return T->nil;
    }
    int r = x->left->cnt+1;
    if(i==r)
        return x;
    else if(i<r)
        return sel(T,x->left,i);
    else
        return sel(T,x->right,i-r);
}

int rank(tree_t* T,node_t* x){
    int r = x->left->cnt+1;
    node_t* y = x;
    while(y!=T->root){
        if(y==parent(T,y)->right)
            r += parent(T,y)->left->cnt + 1;
        y=parent(T,y);
    }
    return r;
}

void pre_order(tree_t* T,node_t* t){
    if(t==T->nil)
    return;
    if(t->color)
        printf(ANSI_COLOR_RED"%d red %d"ANSI_COLOR_RESET"\n",t->key,t->cnt);
    else
        printf(ANSI_COLOR_BLUE"%d black %d"ANSI_COLOR_RESET"\n",t->key,t->cnt);
    pre_order(T,t->left);
    pre_order(T,t->right);
}


int cmd_parse(char* cmd){
    if(strcmp(cmd,"i")==0)
        return 1;
    if(strcmp(cmd,"sel")==0)
        return 2;
    if(strcmp(cmd,"rank")==0)
        return 3;
    if(strcmp(cmd,"pr")==0)
        return 4;
    if(strcmp(cmd,"graph")==0)
        return 5;
    if(strcmp(cmd,"help")==0)
        return 6;
    return -1;
}

