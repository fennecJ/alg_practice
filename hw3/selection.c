#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int ins(int* arr,int len);
int sel(int* arr,int l,int r,int i);
void swap(int *a,int *b);
int partition(int *arr,int l,int r,int key);
int main(int argc,char* argv[]){
srand(time(NULL));
FILE* fi;
FILE* fo;
fi=fopen("input.txt","r");
fo=fopen("output.txt","w");
int len,k;
fscanf(fi,"%d\n%d\n",&len,&k);
int* a = malloc(sizeof(int)*len);
int i = 0;
while(fscanf(fi,"%d\n",a+i)!=EOF)
i++;

int tar = sel(a,0,len-1,k);
printf("%dth smallest number is %d\n",k,tar);
fprintf(fo,"%d\n%d\n%d\n",len,k,tar);
}

int sel(int* arr,int l,int r,int i){
int len = r-l+1;
if(i>0&&i<=len){
    int h_len = ((len+4)/5);
    int hold[h_len];
    int w;
    for(w = 0;w < len/5;w++)
        hold[w]=ins(arr+l+5*w,5);
    if(w*5<len)
        hold[w++] = ins(arr+l+w*5,len%5);
    int med;
    med = (w==1)?(hold[0]):(sel(hold,0,w-1,w/2));
    int q = partition(arr,l,r,med);
    if(q-l == i-1)
    return arr[q];
    else if(q-l>i-1)
        return sel(arr,l,q-1,i);
    else
        return sel(arr,q+1,r,i-q+l-1);
}
}


int ins(int *arr,int len){
    for(int i = 1; i <len; i++){
       int key = arr[i] ;
       int j=i-1 ;
       while(j>=0&&arr[j]>key){
            arr[j+1]=arr[j];
            j=j-1;
            }
        arr[j+1] = key;
    }
    return arr[len/2];
}

void swap(int *a,int *b){
    if(a==b)
    return;
    (*a)^=(*b);
    (*b)^=(*a);
    (*a)^=(*b);
}
int partition(int *arr,int l,int r,int key){
    int k;
    for(k=l;k<r;k++)
        if(arr[k]==key)
        break;
    swap(arr+k,arr+r);
    int j = l-1;
    for(int i = l; i < r; i++)
        if(arr[i]<=key){
            j++;
            swap(arr+j,arr+i);
        }
    swap(arr+j+1,arr+r);
    return j+1;
}