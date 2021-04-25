#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *fi;
    fi = fopen("output.txt", "r");
    int len;
    fscanf(fi, "%d\n", &len);
    int *a = malloc(sizeof(int) * len);
    int i = 0;
    while (fscanf(fi, "%d\n", a + i) != EOF)
        i++;
    for (int j = 1; j < len; j++)
        if (a[j - 1] > a[j])
            printf("Error at %d!\n", j + 2);
}