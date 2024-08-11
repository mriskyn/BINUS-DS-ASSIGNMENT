#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int key;
    struct Node *left, *right;
};

// Fungsi untuk membuat node baru
struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Fungsi untuk melakukan insert tanpa balancing
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

// Fungsi untuk melakukan pencarian
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

    // Insert random data tanpa balancing
    for (int i = 0; i < n; i++) {
        int num = rand();
        root = insert(root, num);
    }

    // Pencarian elemen yang sangat kecil (bisa berada di ujung pohon)
    int key = 0;
    clock_t start = clock();
    struct Node* result = search(root, key);
    clock_t end = clock();

    if (result != NULL)
        printf("Key found\n");
    else
        printf("Key not found\n");

    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time taken for searching in BST: %f seconds\n", time_taken);

    return 0;
}
