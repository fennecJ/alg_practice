#include<stdio.h>
#define global_space=5
struct node
{
    struct node* left;
    struct node* right;
    int key;
    //int times=0;
};
typedef struct node node;
struct tree{
    node* root;
};
typedef struct tree tree;

void search(node* head,int x){
while(head&&head->key!=x){
    if(head->key>x)
    head=head->left;
    else
    head=head->right;
}
return head;
}

void insert(node* head,int x){
    node* ins=malloc(sizeof(node));
    ins->key=x;
    node* tmp=head;
    while(head){
        tmp = head;
        if(x>head->key)
        head=head->left;
        else
        head=head->right;
    }
    if(tmp->key>x)
    tmp->left=ins;
    else
    tmp->right=ins;
}
void print_tree(node* head, int space_count){
if(head){




    
}
}
int main(){
node* head=malloc(sizeof(node));




}