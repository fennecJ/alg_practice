#include <stdio.h>
#include <stdlib.h>

void printArr(int *a, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++)
        printf("%d, ", a[i]);
    printf("%d]", a[len - 1]);
}

int *merge(int *l, int l_len, int *r, int r_len) {
    int len = l_len + r_len;
    int *tmp = malloc(sizeof(int) * len);
    int i, j, k;
    i = j = k = 0;
    for (; i < len; i++) {
        if (j == l_len || k == r_len)
            break;
        if (l[j] < r[k])
            tmp[i] = l[j++];
        else
            tmp[i] = r[k++];
    }
    for (; j < l_len; j++)
        tmp[i++] = l[j];
    for (; k < r_len; k++)
        tmp[i++] = r[k];
    return tmp;
}

int *split(int *a, int len) {
    if (len < 2)
        return a;
    int c = len / 2;
    int *l = split(a, c);
    int *r = split(a + c, len - c);
    return merge(l, c, r, len - c);
}

void printStep(int *a, int len) {
    for (int i = len; i > 0; i /= 2) {
        for (int j = 0; j < len; j += i) {
            printArr(a + j, i);
        }
        printf("\n");
    }

    for (int i = 2; i <= len; i *= 2) {
        for (int j = 0; j < len; j += i) {
            int *tmp = split(a + j, i);
            printArr(tmp, i);
        }
        printf("\n");
    }
}

int main() {
    FILE *fi;
    FILE *fo;
    fi = fopen("input.txt", "r");
    fo = fopen("output.txt", "w");
    int len;
    fscanf(fi, "%d\n", &len);
    int *a = malloc(sizeof(int) * len);
    int i = 0;
    while (fscanf(fi, "%d\n", a + i) != EOF)
        i++;
    int *b = split(a, len);
    printStep(a, len);
    i = 0;
    fprintf(fo, "%d\n", len);
    for (; i < len; i++)
        fprintf(fo, "%d\n", b[i]);
    return 0;
}
