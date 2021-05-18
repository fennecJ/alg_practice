#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void KS(int *, int *, int *, bool **, bool *, int, int);
int main() {
    FILE *fi;
    FILE *fo;
    fi = fopen("input.txt", "r");
    fo = fopen("output.txt", "w");
    int items, max_weight;
    fscanf(fi, "%d", &items);
    fscanf(fi, "%d", &max_weight);
    int *weight = calloc(1, sizeof(int) * items);
    int *cost = calloc(1, sizeof(int) * items);
    int *bag = calloc(1, sizeof(int) * (max_weight + 1));
    bool **rec = calloc(1, sizeof(bool *) * items);
    bool *sel = calloc(1, sizeof(bool));
    for (int i = 0; i < items; i++)
        fscanf(fi, "%d %d", cost + i, weight + i);
    for (int i = 0; i < items; i++)
        rec[i] = calloc(1, sizeof(bool) * (max_weight + 1));
    KS(weight, cost, bag, rec, sel, items, max_weight);
    fprintf(fo, "Total revenue = %d\n", bag[max_weight]);
    fprintf(fo, "Selected item : ");
    for (int i = 0; i < items; i++)
        if (sel[i])
            fprintf(fo, "%d ", i + 1);
}

void KS(int *weight, int *cost, int *bag, bool **rec, bool *sel, int items,
        int max_weight) {
    for (int i = 0; i < items; i++)
        for (int j = max_weight; j >= weight[i]; j--)
            if (bag[j - weight[i]] + cost[i] > bag[j]) {
                bag[j] = bag[j - weight[i]] + cost[i];
                rec[i][j] = true;
            }
    for (int i = items - 1, j = max_weight; i >= 0; --i)
        if (rec[i][j]) {
            sel[i] = true;
            j -= weight[i];
        }
}