#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur Metadata
typedef struct Metadata {
    char fileName[100];
    int fileSize;
    char creationDate[20];
    char modificationDate[20];
    char filePath[200];
} Metadata;

// Struktur Node AVL Tree
struct Node {
    Metadata data;
    struct Node *left;
    struct Node *right;
    int height;
};

// Fungsi untuk mendapatkan tinggi dari node
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Fungsi untuk mendapatkan nilai maksimum
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fungsi untuk membuat node baru
struct Node* newNode(Metadata data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // Node baru ditempatkan di leaf
    return(node);
}

// Fungsi untuk melakukan rotasi kanan
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Lakukan rotasi
    x->right = y;
    y->left = T2;

    // Perbarui tinggi node
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Kembalikan root baru
    return x;
}

// Fungsi untuk melakukan rotasi kiri
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Lakukan rotasi
    y->left = x;
    x->right = T2;

    // Perbarui tinggi node
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Kembalikan root baru
    return y;
}

// Fungsi untuk mendapatkan balance factor dari node
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Fungsi untuk memasukkan metadata baru ke dalam AVL Tree
struct Node* insert(struct Node* node, Metadata data) {
    // 1. Lakukan insert BST normal
    if (node == NULL)
        return(newNode(data));

    if (strcmp(data.fileName, node->data.fileName) < 0)
        node->left = insert(node->left, data);
    else if (strcmp(data.fileName, node->data.fileName) > 0)
        node->right = insert(node->right, data);
    else // Duplicates tidak diizinkan dalam BST
        return node;

    // 2. Perbarui tinggi node ini
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Dapatkan balance factor node ini
    int balance = getBalance(node);

    // Jika node ini tidak balance, ada 4 kasus yang mungkin terjadi

    // Left Left Case
    if (balance > 1 && strcmp(data.fileName, node->left->data.fileName) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(data.fileName, node->right->data.fileName) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(data.fileName, node->left->data.fileName) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(data.fileName, node->right->data.fileName) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Kembalikan pointer node
    return node;
}

// Fungsi untuk menemukan node dengan nilai minimum (terkecil) di AVL Tree
struct Node * minValueNode(struct Node* node) {
    struct Node* current = node;

    // Loop ke kiri untuk menemukan leaf paling kiri
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Fungsi untuk menghapus node dari AVL Tree
struct Node* deleteNode(struct Node* root, char *fileName) {
    // 1. Lakukan delete BST normal
    if (root == NULL)
        return root;

    // Jika nilai yang dihapus lebih kecil dari root
    if (strcmp(fileName, root->data.fileName) < 0)
        root->left = deleteNode(root->left, fileName);

    // Jika nilai yang dihapus lebih besar dari root
    else if (strcmp(fileName, root->data.fileName) > 0)
        root->right = deleteNode(root->right, fileName);

    // Jika nilai yang dihapus adalah root
    else {
        // Node dengan satu atau tanpa child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else {
            // Node dengan dua child
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data.fileName);
        }
    }

    // Jika tree hanya memiliki satu node, kembalikan
    if (root == NULL)
        return root;

    // 2. Perbarui tinggi node ini
    root->height = max(height(root->left), height(root->right)) + 1;

    // 3. Dapatkan balance factor dari node ini
    int balance = getBalance(root);

    // Jika node ini tidak balance, ada 4 kasus yang mungkin terjadi

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Fungsi untuk mencari metadata dalam AVL Tree
struct Node* search(struct Node* root, char *fileName) {
    // Basis kasus: root kosong atau fileName ada di root
    if (root == NULL || strcmp(root->data.fileName, fileName) == 0)
        return root;

    // Nilai fileName lebih besar dari root's fileName
    if (strcmp(root->data.fileName, fileName) < 0)
        return search(root->right, fileName);

    // Nilai fileName lebih kecil dari root's fileName
    return search(root->left, fileName);
}

// Fungsi untuk mencetak metadata (in-order traversal)
void preOrder(struct Node *root) {
    if(root != NULL) {
        printf("File Name: %s\n", root->data.fileName);
        printf("File Size: %d bytes\n", root->data.fileSize);
        printf("Creation Date: %s\n", root->data.creationDate);
        printf("Modification Date: %s\n", root->data.modificationDate);
        printf("File Path: %s\n\n", root->data.filePath);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    struct Node *root = NULL;

    Metadata file1 = {"file1.txt", 1024, "2024-07-01", "2024-08-10", "/Users/ryz/Documents/BOL/BINUS-DS-ASSIGNMENT/DS/exam/file1.txt"};
    Metadata file2 = {"file2.txt", 2048, "2024-07-02", "2024-08-11", "/Users/ryz/Documents/BOL/BINUS-DS-ASSIGNMENT/DS/exam/file2.txt"};
    Metadata file3 = {"file3.txt", 512, "2024-07-03", "2024-08-12", "/Users/ryz/Documents/BOL/BINUS-DS-ASSIGNMENT/DS/exam/file3.txt"};

    root = insert(root, file1);
    root = insert(root, file2);
    root = insert(root, file3);

    printf("Preorder traversal of the constructed AVL tree is:\n");
    preOrder(root);

    printf("\nDeleting file2.txt\n");
    root = deleteNode(root, "file2.txt");

    printf("Preorder traversal after deletion of file2.txt:\n");
    preOrder(root);

    struct Node* found = search(root, "file1.txt");
    if (found != NULL) {
        printf("\nfile1.txt found!\n");
        printf("File Size: %d bytes\n", found->data.fileSize);
        printf("Creation Date: %s\n", found->data.creationDate);
        printf("Modification Date: %s\n", found->data.modificationDate);
        printf("File Path: %s\n", found->data.filePath);
    } else {
        printf("\nfile1.txt not found!\n");
    }

    return 0;
}
