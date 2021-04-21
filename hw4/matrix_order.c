#include<stdio.h>
#include<stdlib.h>
int main(){

    FILE* fi;
    FILE* fo;
    fi=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    int k;
    int len=0;
    while(fscanf(fi,"%d\n",&k)!=EOF){
    len++;
    printf("%d\n",len);
    }
    fclose(fi);
    fi=fopen("input.txt","r");
    int* a = malloc(sizeof(int)*len);
    for(k=0;k<len;k++){
        fscanf(fi,"%d\n",a+k);
    }
    
    /*
    while(fscanf(fi,"%d\n",a+i)!=EOF)
    i++;*/

    
    //while(fscanf(fi,"%d\n",a+i)!=EOF)
    

}