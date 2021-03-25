#include<stdio.h>
#include<stdlib.h>
int* merge(int* l,int l_len,int* r,int r_len){
int len = l_len + r_len;
int *tmp = malloc(sizeof(int)*len);
int i,j,k;
i = j = k = 0;
for( ; i < len ; i++){
if(j == l_len || k== r_len)
break;
if(l[j]<r[k])
tmp[i] = l[j++];
else
tmp[i] = r[k++];
}
for(;j<l_len;j++)
tmp[i++] = l[j];
for(;k<r_len;k++)
tmp[i++] = r[k];
return tmp;
}
int* split(int* a,int len){
    if(len<2)
    return a;
int c = len / 2;
int* l = a;
int* r = &(a[c]);
int* ll = split(l,c);
int* rr = split(r,len-c);
return  merge(ll,c,rr,len-c);
}

int main(){
FILE* fi,fo;
fi=fopen("input.txt","r");
fo=fopen("output.txt","w");
int len;
fscanf(fi,"%d\n",&len);
int* a = malloc(sizeof(int)*len);
int i = 0;
while(fscanf(fi,"%d\n",a+i)!=EOF)
i++;
int* b = split(a,len);
i = 0;
for( ; i < len ; i++)
fprintf(fo,"%d\n",b[i]);
return 0;
}