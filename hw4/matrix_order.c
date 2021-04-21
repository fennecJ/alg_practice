#include<stdio.h>
#include<stdlib.h>
int main(){

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


}