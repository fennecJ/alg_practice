#include<stdio.h>
#include<stdlib.h>
void swap(int *a,int *b){
    if(a==b)
    return;
    (*a)^=(*b);
    (*b)^=(*a);
    (*a)^=(*b);
}
int main(){
FILE* fo;
fo=fopen("input.txt","w");
int len = 10000;
int arr[len];
for(int i = 0;i<len;i++)
    arr[i]=i+1;
for(int i = 0;i<len;i++)
    if((i+1)%400==0)
        swap(arr+i,arr+i-199);
fprintf(fo,"%d\n",len);
for(int i = 0; i < len ; i++)
fprintf(fo,"%d\n",arr[i]);
return 0;

}