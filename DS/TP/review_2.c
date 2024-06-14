#include <stdio.h>
#include <stdlib.h>

// Definisi struktur node
struct Node {
    int data;
    struct Node* next;
};

// Fungsi untuk menambahkan node baru di akhir daftar
void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = *head_ref;
        return;
    }

    while (last->next != *head_ref) {
        last = last->next;
    }

    last->next = new_node;
}

// Fungsi untuk mencetak daftar
void printList(struct Node* head) {
    struct Node* temp = head;
    if (head != NULL) {
        do {
            printf("%d -> ", temp->data);
            temp = temp->next;
        } while (temp != head);
    }
    printf("HEAD\n");
}

int main() {
    struct Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);

    printList(head);

    return 0;
}
