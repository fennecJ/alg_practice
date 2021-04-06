#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void swap(int *a,int *b);
int part(int *arr,int l,int r);
void qksort(int *arr,int l,int r,int k);
void ins(int *arr,int l,int r);
int main(int argc,char* argv[]){
srand(time(NULL));
FILE* fi;
FILE* fo;
FILE* fo2;
fi=fopen("input.txt","r");
fo=fopen("output.txt","w");
int len;
fscanf(fi,"%d\n",&len);
int* a = malloc(sizeof(int)*len);
int* b = malloc(sizeof(int)*len);
int i = 0;
while(fscanf(fi,"%d\n",b+i)!=EOF)
i++;
clock_t start, end;
int cpu_time_used;
int ckt = 999999999;
if(argc==1){
for(int k = 0;k<len;k++){
start = clock(); 
memcpy(a,b,sizeof(int)*len);
qksort(a,0,len-1,k);
i = 0;
end = clock();
cpu_time_used = end - start;
if(cpu_time_used<ckt){
ckt = cpu_time_used;
printf("%d %d\n",k,cpu_time_used);
}
}
}else
{
    int k = atoi(argv[1]);
    qksort(b,0,len-1,k);
}
fprintf(fo,"%d\n",len);
for( ; i < len ; i++)
if(argc==1)
fprintf(fo,"%d\n",a[i]);
else
fprintf(fo,"%d\n",b[i]);
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
    if(l-r+1<=k){
    ins(arr,l,r+1);
    return;
    }
    else{
    int q = part(arr,l,r);
    qksort(arr,l,q-1,k);
    qksort(arr,q+1,r,k);
    }

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