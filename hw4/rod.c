#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
int *max_profit(int *price, int rod_len, int *);

int *tst(const int *price, int rod_len, int *tt) {
    int *r = malloc(sizeof(int) * (rod_len + 1));
    for (int i = 0; i <= rod_len; i++)
        r[i] = INT_MIN;
    cut(price, rod_len, r, tt);
    return r;
}

int cut(const int *price, int rod_len, int *r) {
    if (r[rod_len] >= 0)
        return r[rod_len];
    int q;
    if (rod_len == 0)
        q = 0;
    else {
        q = INT_MIN;
        for (int i = 1; i <= rod_len; i++) {
            if (i > 11) {
                if (q < cut(price, rod_len - i, r))
                    q = cut(price, rod_len - i, r);
            } else if (q < price[i] + cut(price, rod_len - i, r)) {
                q = price[i] + cut(price, rod_len - i, r);
            }
        }
    }
    r[rod_len] = q;
    return q;
}

int *max_profit(int *price, int rod_len, int *tmps) {
    int *r = malloc(sizeof(int) * (rod_len + 1));
    r[0] = 0;
    for (int i = 1; i <= rod_len; i++) {
        int q = INT_MIN;
        for (int j = 1; j <= i; j++) {
            int tmp;
            if (j > rod_len)
                tmp = r[i - j];
            else
                tmp = price[j] + r[i - j];
            if (q < tmp) {
                q = tmp;
                tmps[i] = j;
            }
        }
        r[i] = q;
    }
    return r;
}
int main() {
    int price[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int len;
    int tmps[55] = {0};
    int *r = max_profit(price, 50, tmps);

    int k = 50;
    for (int i = 0; i < 10; i++) {
        printf("%d ", tmps[k]);
        k -= tmps[k];
    }
}