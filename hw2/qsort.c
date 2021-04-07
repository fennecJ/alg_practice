#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
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

int main(int argc,char* argv[]){
FILE* fi;
FILE* fo;
clock_t start, end;
double cpu_time_used;
fi=fopen("input.txt","r");
fo=fopen("output.txt","w");
int len;
fscanf(fi,"%d\n",&len);
int* a = malloc(sizeof(int)*len);
int i = 0;
while(fscanf(fi,"%d\n",a+i)!=EOF)
i++;
start = clock(); 
qksort(a,0,len-1);
end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
if(argc==2)
if(strcmp(argv[1],"-st")==0)
printf("Time Cost:%f\n", cpu_time_used);

i = 0;
fprintf(fo,"%d\n",len);
for( ; i < len ; i++)
fprintf(fo,"%d\n",a[i]);
return 0;
}