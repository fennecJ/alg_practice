#include<stdio.h>
#include <stdlib.h>
void swap(int *a,int *b);
int part(int *arr,int l,int r);
void qksort(int *arr,int l,int r,int k);
void ins(int *arr,int l,int r);
int main(){
FILE* fi;
FILE* fo;
FILE* fo2;
fi=fopen("input.txt","r");
fo=fopen("output.txt","w");
fo2=fopen("k_record.txt","w");
int len;
fscanf(fi,"%d\n",&len);
int* a = malloc(sizeof(int)*len);
int i = 0;
while(fscanf(fi,"%d\n",a+i)!=EOF)
i++;
qksort(a,0,len-1,20);
i = 0;
fprintf(fo,"%d\n",len);
for( ; i < len ; i++)
fprintf(fo,"%d\n",a[i]);
return 0;
}

void swap(int *a,int *b){
    if(a==b)
    return;
    (*a)^=(*b);
    (*b)^=(*a);
    (*a)^=(*b);
}
int part(int *arr,int l,int r){
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

void qksort(int *arr,int l,int r,int k){
    if(l>=r)
    return;
    int q;
    if(l-r+1<=k){
    ins(arr,l,r+1);
    q=r;
    }
    else
    q = part(arr,l,r);
    qksort(arr,l,q-1,k);
    qksort(arr,q+1,r,k);

}
void ins(int *arr,int l,int r){
    for(int i = l; i < r; i++){
       int key = arr[i];
       int j=i-1 ;
       while(j>=l&&arr[j]>key){
            arr[j+1]=arr[j];
            j=j-1;
            }
        arr[j+1] = key;
    }
}