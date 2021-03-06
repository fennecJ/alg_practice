#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void swap(int *a, int *b);
int part(int *arr, int l, int r);
void qksort(int *arr, int l, int r, int k);
void ins(int *arr, int l, int r);
void oqsort(int *arr, int l, int r);
int main(int argc, char *argv[]) {
    srand(time(NULL));
    FILE *fi;
    FILE *fo;
    fi = fopen("input.txt", "r");
    fo = fopen("output.txt", "w");
    int len;
    fscanf(fi, "%d\n", &len);
    int *b = malloc(sizeof(int) * len);
    int i = 0;
    while (fscanf(fi, "%d\n", b + i) != EOF)
        i++;
    clock_t start, end;
    double cpu_time_used;
    if (argc == 1) {
        printf("You didn't send any Argument!\nAvailable "
               "candidate:\ni:insertion_sort\nq:quick_sort\n{Integer}:Hybrid "
               "quick_sort with k = {Integer}\nYou can monitor the time cost "
               "with -st in second  Argument\n");
    } else {
        start = clock();
        int k = atoi(argv[1]);
        if (argv[1][0] == 'q')
            oqsort(b, 0, len - 1);
        else if (argv[1][0] == 'i')
            ins(b, 0, len);
        else
            qksort(b, 0, len - 1, k);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    if (argc == 3)
        if (strcmp(argv[2], "-st") == 0)
            printf("Time Cost:%f\n", cpu_time_used);
    fprintf(fo, "%d\n", len);
    for (i = 0; i < len; i++)
        fprintf(fo, "%d\n", b[i]);
    return 0;
}

void swap(int *a, int *b) {
    if (a == b)
        return;
    (*a) ^= (*b);
    (*b) ^= (*a);
    (*a) ^= (*b);
}
int part(int *arr, int l, int r) {
    int key = arr[r];
    int j = l - 1;
    for (int i = l; i < r; i++)
        if (arr[i] <= key) {
            j++;
            swap(arr + j, arr + i);
        }
    swap(arr + j + 1, arr + r);
    return j + 1;
}

void qksort(int *arr, int l, int r, int k) {
    if (l >= r)
        return;
    if (r - l > k) {
        int q = part(arr, l, r);
        qksort(arr, l, q - 1, k);
        qksort(arr, q + 1, r, k);
    } else {
        ins(arr, l, r + 1);
        return;
    }
}

void oqsort(int *arr, int l, int r) {
    if (l >= r)
        return;
    else {
        int q = part(arr, l, r);
        oqsort(arr, l, q - 1);
        oqsort(arr, q + 1, r);
    }
}

void ins(int *arr, int l, int r) {
    for (int i = l; i < r; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= l && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}