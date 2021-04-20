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
void insert(tree_t* T,int x);
void print_tree(tree_t* T,node_t* root, int i,int tar);
node_t* max_node(node_t* head);
node_t* min_node(node_t* head);
node_t* suc(tree_t* T,node_t* head);
node_t* pred(tree_t* T,node_t* head);
void transp(tree_t* T,node_t* u,node_t* v);
void delete(tree_t* T,node_t* z);
node_t* parent(tree_t* T,node_t* tar);
void l_rotate(tree_t* T,node_t* x);
void r_rotate(tree_t* T,node_t* x);
void rb_insert(tree_t* T,node_t* z);
//void mod_parent(tree_t* T,node_t* tar,node_t* post);
int cmd_parse(char* cmd);
void FIX(tree_t* T,node_t* z);

int main(){
tree_t* T=new_tree();
char cmd[10];
int tmp;
node_t* t;
printf("Available commands:\ns {int} - search for specific node with selected key {int}\nmax - return max from tree\nmin - return min from tree\nsu {int} - search for successor of specific node with selected key {int}\npr {int} - search for predecessor of specific node with selected key {int}\ni {int} - insert node with key {int} into tree\nd {int} - delete specific node with selected key {int}\npar {int} - return the parent of specific node with selected key {int}\nhelp - print the help\nq - exit\n");
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
            printf("Finding %d in tree\n",tmp);
            if(search(T,T->root,tmp))
            print_tree(T,T->root,0,tmp);
            else
            printf("%d was not found!!\n",tmp);
            break;
        case 2:
            printf("Finding max element in tree\n");
            if(T->root){
            t=max_node(T->root);
            printf("Max element is %d\n",t->key);
            print_tree(T,T->root,0,t->key);
            }else
            printf("The tree was empty!!\n");
        break;
        case 3:
            printf("Finding min element in tree\n");
            if(T->root){
            t=min_node(T->root);
            printf("min element is %d\n",t->key);
            print_tree(T,T->root,0,t->key);
            }else
            printf("The tree was empty!!\n");
        break;
        case 4:
            scanf("%d",&tmp);
            printf("Finding successor of %d in tree\n",tmp);
            t=search(T,T->root,tmp);
            if(t){
                t=suc(T,t);
                if(t){
                printf("Successor of %d in tree: %d\n",tmp,t->key);
                print_tree(T,T->root,0,t->key);
                }else
                printf("%d have no successor!!\n",tmp);
            }else
            printf("%d was not in the tree!!\n",tmp);
        break;
        case 5:
            scanf("%d",&tmp);
            printf("Finding predecessor of %d in tree\n",tmp);
            t=search(T,T->root,tmp);
            if(t){
                t=pred(T,t);
                if(t){
                printf("Predecessor of %d in tree: %d\n",tmp,t->key);
                print_tree(T,T->root,0,t->key);
                }else
                printf("%d have no predecessor!!\n",tmp);
            }else
            printf("%d was not in the tree!!\n",tmp);
        break;
        case 6:
            scanf("%d",&tmp);
            printf("Insert %d into tree\n",tmp);
            t=new_node(T,tmp);

            rb_insert(T,t);
            print_tree(T,T->root,0,t->key);
        break;
        case 7:
            scanf("%d",&tmp);
            printf("Delete %d from tree\n",tmp);
            t=search(T,T->root,tmp);
            if(t!=T->nil)
            if(t->cnt>1){
            t->cnt--;
            print_tree(T,T->root,0,tmp);
            }
            else{
                delete(T,t);
                print_tree(T,T->root,0,tmp);
            }else
            printf("%d was not in the tree!!\n",tmp);
        break;
        case 8:
            scanf("%d",&tmp);
            printf("Finding parent of %d in tree\n",tmp);
            node_t* p=parent(T,search(T,T->root,tmp));
            if(p!=T->nil)
            print_tree(T,T->root,0,p->key);
            else
            printf("Parent not found\n");
        break;
        case 9:
            printf("Available commands:\ns {int} - search for specific node with selected key {int}\nmax - return max from tree\nmin - return min from tree\nsu {int} - search for successor of specific node with selected key {int}\npr {int} - search for predecessor of specific node with selected key {int}\ni {int} - insert node with key {int} into tree\nd {int} - delete specific node with selected key {int}\npar {int} - return the parent of specific node with selected key {int}\nhelp - print the help\nq - exit\n");
            break;
        case 10:
            scanf("%d",&tmp);
            printf("left-rotate at %d\n",tmp);
            t = search(T,T->root,tmp);
            l_rotate(T,t);
            print_tree(T,T->root,0,t->key);
            break;
        case 11:
            scanf("%d",&tmp);
            printf("right-rotate at %d\n",tmp);
            t = search(T,T->root,tmp);
            r_rotate(T,t);
            print_tree(T,T->root,0,t->key);
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
    T->nil->cnt=1;
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
            else if (z==parent(T,z)->right)
            {
                z=parent(T,z);
                l_rotate(T,z);
            }
            parent(T,z)->color=BLK;
            parent(T,parent(T,z))->color=RED;
            r_rotate(T,parent(T,parent(T,z)));
        }else{
            node_t* y = parent(T,parent(T,z))->left;
            if(y->color==RED){
                parent(T,z)->color=BLK;
                y->color=BLK;
                parent(T,parent(T,z))->color=RED;
                z=parent(T,parent(T,z));
            }
            else if (z==parent(T,z)->left)
            {
                z=parent(T,z);
                r_rotate(T,z);
            }
            parent(T,z)->color=BLK;
            parent(T,parent(T,z))->color=RED;
            l_rotate(T,parent(T,parent(T,z)));
        }
    }
T->root->color=BLK;
}




void insert(tree_t* T,int x){
    node_t* head=T->root;
    node_t* ins=new_node(T,x);
    if(!head){
    T->root=ins;
    return;
    }
    node_t* tmp=NULL;
    while(head!=T->nil){
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
void print_tree(tree_t* T,node_t* root, int i,int tar){
    if(root==T->nil){
        if(i!=0)
        print_tab(i-1);
    printf("|======="ANSI_COLOR_BLUE"N"ANSI_COLOR_RESET"\n");
    return;
    }
    print_tree(T,root->right,i+1,tar);
    if(i!=0){
        print_tab(i-1);
            if(root->key==tar){
                if(root->color==RED)
                printf("|======="ANSI_COLOR_RED"{%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
                else
                printf("|======="ANSI_COLOR_BLUE"{%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            }
            else if(root->color==RED)
            printf("|======="ANSI_COLOR_RED"%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            else printf("|======="ANSI_COLOR_BLUE"%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            
    }else{
            if(root->key==tar){
                if(root->color==RED)
                printf(ANSI_COLOR_RED"{%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
                else
                printf(ANSI_COLOR_BLUE"{%d[%d]}"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            }
            else if(root->color==RED)
            printf(ANSI_COLOR_RED"%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
            else printf(ANSI_COLOR_BLUE"%d[%d]"ANSI_COLOR_RESET"\n",root->key,root->cnt);
    }
    print_tree(T,root->left,i+1,tar);
}

node_t* max_node(node_t* head){
    while(head->right)
    head=head->right;
    return head;
}

node_t* min_node(node_t* head){
    while(head->left)
    head=head->left;
    return head;
}

node_t* suc(tree_t* T,node_t* head){
    if(head->right)
        return min_node(head->right);
    node_t* y = parent(T,head);
    while(y&&head==y->right){
        head=y;
        y=parent(T,y);
    }
    return y;
}

node_t* pred(tree_t* T,node_t* head){
    if(head->left)
        return max_node(head->left);
    node_t* y = parent(T,head);
    while(y&&head==y->left){
        head=y;
        y=parent(T,y);
    }
    return y;
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

void transp(tree_t* T,node_t* u,node_t* v){
    if(parent(T,u)==NULL)
        T->root=v;
    else if(u==(parent(T,u)->left))
    parent(T,u)->left=v;
    else
    parent(T,u)->right=v;
}

void delete(tree_t* T,node_t* z){
    if(z->left==NULL)
        transp(T,z,z->right);
    else if(z->right==NULL)
        transp(T,z,z->left);
    else{
        node_t* y = min_node(z->right);
        if(parent(T,y)!=z){
            transp(T,y,y->right);
            y->right=z->right;
        }
        transp(T,z,y);
        y->left=z->left;
    }
    free(z);
}


void l_rotate(tree_t* T,node_t* x){
    //printf("Call l_rotate at %d\n",x->key);
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
    //printf("Call r_rotate at %d\n",x->key);
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





int cmd_parse(char* cmd){
    if(strcmp(cmd,"s")==0)
        return 1;
    if(strcmp(cmd,"max")==0)
        return 2;
    if(strcmp(cmd,"min")==0)
        return 3;
    if(strcmp(cmd,"su")==0)
        return 4;
    if(strcmp(cmd,"pr")==0)
        return 5;
    if(strcmp(cmd,"i")==0)
        return 6;
    if(strcmp(cmd,"d")==0)
        return 7;
    if(strcmp(cmd,"par")==0)
        return 8;
    if(strcmp(cmd,"help")==0)
        return 9;
    if(strcmp(cmd,"lr")==0)
        return 10;
    if(strcmp(cmd,"rr")==0)
        return 11;
    return -1;
}

