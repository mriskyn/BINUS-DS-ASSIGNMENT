#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int key;
    struct Node *left, *right;
    int height;
};

// Fungsi untuk mendapatkan tinggi dari node
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Fungsi untuk membuat node baru
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

// Rotasi kanan
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;
    x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;

    return x;
}

// Rotasi kiri
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;
    y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;

    return y;
}

// Mendapatkan balance factor dari node N
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Fungsi untuk insert dengan AVL balancing
struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Fungsi pencarian
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

int main() {
    struct Node *root = NULL;
    int n = 1000000; // Jumlah node
    srand(time(0));

    // Insert random data dengan AVL balancing
    for (int i = 0; i < n; i++) {
        int num = rand();
        root = insert(root, num);
    }

    // Pencarian elemen yang sangat kecil
    int key = 0;
    clock_t start = clock();
    struct Node* result = search(root, key);
    clock_t end = clock();

    if (result != NULL)
        printf("Key found\n");
    else
        printf("Key not found\n");

    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken for searching in AVL Tree: %f seconds\n", time_taken);

    return 0;
}
