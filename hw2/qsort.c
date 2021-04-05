#include<stdio.h>
#include<stdlib.h>
void swap(int *a,int *b){
    if(a==b)
    return;
    (*a)^=(*b);
    (*b)^=(*a);
    (*a)^=(*b);
}
int partition(int *arr,int l,int r){
    int key=arr[r];
    int j = l-1;
    for(int i = l; i < r; i++)
        if(arr[i]<=key){
            j++;
            swap(arr+j,arr+i);
        }
    swap(arr+j+1,arr+r);
    return j+1;
}

void qksort(int *arr,int l,int r){
    if(l>=r)
    return;
    int q = partition(arr,l,r);
    qksort(arr,l,q-1);
    qksort(arr,q+1,r);
}

int main(){
int a[9]={5,7,3,2,1,1,5,7,6};
qksort(a,0,8);
for(int i = 0;i<9;i++)
printf("%d ",a[i]);
printf("\n");
}