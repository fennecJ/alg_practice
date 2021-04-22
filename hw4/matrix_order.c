#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
void MCO(int *a, int **m, int **s, int len);
void POP(int **s, int i, int j);
int main() {

    FILE *fi;
    FILE *fo;
    fi = fopen("input.txt", "r");
    fo = fopen("output.txt", "w");
    int k;
    int len = 0;
    while (fscanf(fi, "%d\n", &k) != EOF) {
        len++;
    }
    fclose(fi);
    fi = fopen("input.txt", "r");
    int *a = malloc(sizeof(int) * len);
    for (k = 0; k < len; k++) {
        fscanf(fi, "%d\n", a + k);
    }
    // int m[len][len], s[len][len];
    int **m, **s;
    m = (int **)malloc(sizeof(int *) * len);
    s = (int **)malloc(sizeof(int *) * len);
    for (k = 0; k < len; k++) {
        m[k] = (int *)malloc(sizeof(int) * len);
        s[k] = (int *)malloc(sizeof(int) * len);
    }
    // printf("1\n");
    MCO(a, m, s, len);
    // printf("2\n");
    for (int i = 1; i < len; i++) {
        for (int j = i; j < len; j++)
            printf("%d ", s[i][j]);
        printf("\n");
    }

    POP(s, 1, len - 1);
    printf("\n");
    /*
    while(fscanf(fi,"%d\n",a+i)!=EOF)
    i++;*/

    // while(fscanf(fi,"%d\n",a+i)!=EOF)
}

void MCO(int *a, int **m, int **s, int len) {
    int n = len;
    for (int i = 0; i < n; i++)
        m[i][i] = 0;
    for (int l = 1; l < n; l++) {
        for (int i = 0; i + l < n; i++) {
            int j = i + l;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + a[i] * a[k] * a[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}
void POP(int **s, int i, int j) {
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        POP(s, i, s[i][j]);
        POP(s, s[i][j] + 1, j);
        printf(")");
    }
}