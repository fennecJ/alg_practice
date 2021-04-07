#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
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
ins(a,len);
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