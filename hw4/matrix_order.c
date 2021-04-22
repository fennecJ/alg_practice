#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
void MCO(int *a, int **m, int **s, int len);
void POP(int **s, int i, int j, FILE *fo);
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
    int **m, **s;
    m = (int **)malloc(sizeof(int *) * len);
    s = (int **)malloc(sizeof(int *) * len);
    for (k = 0; k < len; k++) {
        m[k] = (int *)malloc(sizeof(int) * len);
        s[k] = (int *)malloc(sizeof(int) * len);
    }
    MCO(a, m, s, len);
    /* Visualize the result of s
    for (int i = 1; i < len; i++) {
        for (int k = 0; k < i; k++)
            printf("  ");
        for (int j = i; j < len; j++) {
            printf("%d ", s[i][j]);
        }
        printf("\n");
    }
    */
    fprintf(fo, "%d\n", m[1][len - 1]);
    POP(s, 1, len - 1, fo);
    printf("\n");
}

void MCO(int *a, int **m, int **s, int len) {
    int n = len;
    for (int i = 1; i < n; i++)
        m[i][i] = 0;
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + a[i - 1] * a[k] * a[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}
void POP(int **s, int i, int j, FILE *fo) {
    if (i == j)
        fprintf(fo, "A%d", i);
    else {
        fprintf(fo, "(");
        POP(s, i, s[i][j], fo);
        POP(s, s[i][j] + 1, j, fo);
        fprintf(fo, ")");
    }
}