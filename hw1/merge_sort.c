#include<stdio.h>
#include<stdlib.h>

void split(int* a,int len){
int c = len / 2;
int* l = malloc(sizeof(int)*c);
int* r = malloc(sizeof(int)*(len-c));
int i,j,k;
i = j = k = 0;
for(;i < len; i++){
if(i<c)
l[j++] = a[i];
else
r[k++] = a[i];
}
printf("---------------------\n");
i = 0;
for(; i < len; i++){
if(i<c)
printf("%d " ,l[i]);
else
printf("%d " ,r[i-c]);
}

}

int* merge(int* a,int* b){

}
int main(){
int a[9]={0,1,2,3,4,5,6,7,8};
split(a,9);


}