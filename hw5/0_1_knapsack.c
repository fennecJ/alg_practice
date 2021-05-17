#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *fi;
    FILE *fo;
    fi = fopen("input.txt", "r");
    fo = fopen("output.txt", "w");
    int items, max_weight;
    fscanf(fi, "%d", &items);
    fscanf(fi, "%d", &max_weight);
    int **ref = calloc(1, sizeof(int *) * items);
    for (int i = 0; i < items; i++)
        ref[i] = calloc(1, sizeof(int) * 2);
    for (int i = 0; i < items; i++)
        fscanf(fi, "%d %d", &ref[i][0], &ref[i][1]);

    // ref[items][0] = item's value
    // ref[items][1] = item's weight
}