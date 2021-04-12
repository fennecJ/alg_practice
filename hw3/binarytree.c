#include<stdio.h>

struct node
{
    struct node* left;
    struct node* right;
    int key;
    int times=0;
};

typedef struct node node;

void search(node* head,int x){

}

void insert(node* head,int x){
node* leaf=malloc(sizeof(node));
leaf->key=x;
if(!head)
    head=key;
else while(head->left->key>x&&head->left)
head=head->left;

}

int main(){
node* head;







}