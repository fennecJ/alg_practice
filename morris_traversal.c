#include <stdio.h>
#include <stdlib.h>

typedef struct __node node;
struct __node {
    int data;
    node *left;
    node *right;
};

node *new_node(int data);
node *build_tree(char *arr[], int i, int n);
void print_tree(node *root, int i); // Print 2D tree in 90 degrees CCW
void print_tab(int);
void inOrder(node *);
void preOrder(node *);
void morris_inOrder(node *);
void morris_preOrder(node *);
void invert_bin_tree(node *root);
void invert_bin_tree2(node *root);
void invert_bin_tree3(node *root);
void swap(node **a, node **b);

int main() {
    char *datas[] = {"1", "2", "3", "4", "5", "n", "7",
                     "n", "n", "n", "n", "n", "n", "14"};
    node *root = build_tree(datas, 0, 14);
    /*
    preOrder(root);
    printf("\n\n");
    morris_preOrder(root);
    printf("\n\n");
    */
    print_tree(root, 0); // Print 2D tree in 90 degrees CCW
    invert_bin_tree3(root);
    printf("\n\n");
    print_tree(root, 0);
}

node *new_node(int data) {
    node *t = malloc(sizeof(node));
    t->data = data;
    t->left = NULL;
    t->right = NULL;
    return t;
}

node *build_tree(char *arr[], int i, int n) {
    node *root = NULL;
    if (i < n) {
        int a = atoi(arr[i]);
        if (arr[i][0] == 'n')
            return NULL;
        root = new_node(a);
        root->left = build_tree(arr, 2 * i + 1, n);
        root->right = build_tree(arr, 2 * i + 2, n);
    }
    return root;
}

inline void print_tab(int i) {
    for (int j = 0; j < i; j++)
        printf("|\t");
}

void print_tree(node *root, int i) {
    if (root == NULL)
        return;
    print_tree(root->right, i + 1);
    if (i != 0) {
        print_tab(i - 1);
        printf("|=======%d\n", root->data);
    } else {
        printf("%d\n", root->data);
    }
    print_tree(root->left, i + 1);
}

void morris_inOrder(node *head) {
    node *cur = head;
    while (cur) {
        node *q = cur->left;
        if (q) {
            while (q->right && q->right != cur)
                q = q->right;

            if (!q->right) {
                q->right = cur;
                cur = cur->left;
                continue;
            }
            q->right = NULL;
        }
        printf("%d ", cur->data);
        cur = cur->right;
    }
}

void morris_preOrder(node *head) {
    node *cur = head;
    while (cur) {
        node *q = cur->left;
        if (q) {
            while (q->right && q->right != cur)
                q = q->right;

            if (!q->right) {
                q->right = cur;
                printf("%d ", cur->data);
                cur = cur->left;
                continue;
            }
            q->right = NULL;
            cur = cur->right;
            continue;
        }
        printf("%d ", cur->data);
        cur = cur->right;
    }
}

inline void swap(node **a, node **b) {
    node *tmp = *a;
    *a = *b;
    *b = tmp;
}

void invert_bin_tree(node *root) {
    node *cur = new_node(0);
    cur->left = root;
    while (cur) {
        node *q = cur->left;
        if (q) {
            while (q->right && q->right != cur)
                q = q->right;
            if (!q->right) {
                q->right = cur;
                cur = cur->left;
                continue;
            }
            node *tmp = cur->left;
            while (tmp) {
                swap(&tmp->left, &tmp->right);
                if (tmp == q)
                    break;
                tmp = tmp->left;
            }
            q->left = NULL;
        }
        cur = cur->right;
    }
}

void invert_bin_tree2(node *root) {
    node *cur = root;
    while (cur) {
        node *q = cur->left;
        if (q) {
            while (q->left && q->left != cur)
                q = q->left;

            if (!q->left) {
                q = cur->left;
                while (q->right)
                    q = q->right;

                q->right = cur;
            } else {
                q->left = NULL;
                swap(&cur->left, &cur->right);
            }
            cur = cur->left;
            continue;
        }
        swap(&cur->left, &cur->right);
        cur = cur->left;
    }
}

void invert_bin_tree3(node *root) {
    node *cur = root;
    while (cur) {
        node *q = cur->left;
        if (q) {
            while (q->left && q->left != cur)
                q = q->left;
            if (!q->left) {
                q = cur->left;
                while (q->right)
                    q = q->right;

                q->right = cur;
                cur = cur->left;
                continue;
            }
            q->left = NULL;
        }
        swap(&cur->right, &cur->left);
        cur = cur->left;
    }
}

void invert_bin_tree3A(node *root) {
    node *cur = root;
    while (cur) {
        node *q = cur->left;
        if (q) {
            while (q->left && q->left != cur)
                q = q->left;
            if (!q->left) {
                q = cur->left;
                while (q->right && q->right != cur)
                    q = q->right;
                if (!q->right) {
                    q->right = cur;
                    cur = cur->left;
                    continue;
                }
            }
            q->left = NULL;
        }
        swap(&cur->right, &cur->left);
        cur = cur->left;
    }
}

void inOrder(node *root) {
    if (!root)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void preOrder(node *root) {
    if (!root)
        return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}