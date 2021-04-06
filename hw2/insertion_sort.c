#include<stdio.h>
#include<stdlib.h>
void ins(int *arr,int len){
    for(int i = 1; i <len; i++){
       int key = arr[i] ;
       int j=i-1 ;
       while(j>=0&&arr[j]>key){
            arr[j+1]=arr[j];
            j=j-1;
            }
        arr[j+1] = key;
    }
}
int main(){
FILE* fi;
FILE* fo;
fi=fopen("input.txt","r");
fo=fopen("output.txt","w");
int len;
fscanf(fi,"%d\n",&len);
int* a = malloc(sizeof(int)*len);
int i = 0;
while(fscanf(fi,"%d\n",a+i)!=EOF)
i++;
ins(a,len);
i = 0;
fprintf(fo,"%d\n",len);
for( ; i < len ; i++)
fprintf(fo,"%d\n",a[i]);
return 0;
}