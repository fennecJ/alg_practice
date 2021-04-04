#include<stdio.h>
#include<stdlib.h>
void insertion(int *arr,int len){
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
int a[9]={5,4,3,2,1,1,5,7,6};
insertion(a,9);
for(int i = 0;i<9;i++)
printf("%d ",a[i]);
printf("\n");
}