#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 30
#define MAX_POSITION 50
#define MAX_ENTRIES 5

// Definisi struktur Karyawan
struct Employee {
    int id;
    char name[MAX_NAME];
    char birthPlace[MAX_NAME];
    char birthDate[MAX_NAME];
    char position[MAX_POSITION];
    struct Employee* next;
};

// Fungsi untuk menambah data karyawan
void push(struct Employee** head_ref, int id, char name[], char birthPlace[], char birthDate[], char position[]) {
    if (*head_ref != NULL) {
        struct Employee* temp = *head_ref;
        int count = 1;
        while (temp->next != NULL) {
            count++;
            temp = temp->next;
        }
        if (count >= MAX_ENTRIES) {
            printf("Database penuh. Tidak bisa menambah data.\n");
            return;
        }
    }
    
    struct Employee* new_node = (struct Employee*)malloc(sizeof(struct Employee));
    new_node->id = id;
    strcpy(new_node->name, name);
    strcpy(new_node->birthPlace, birthPlace);
    strcpy(new_node->birthDate, birthDate);
    strcpy(new_node->position, position);
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        struct Employee* last = *head_ref;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
}

// Fungsi untuk menampilkan data karyawan
void display(struct Employee* head) {
    struct Employee* temp = head;
    if (head == NULL) {
        printf("Database kosong.\n");
        return;
    }
    printf("Daftar Karyawan:\n");
    while (temp != NULL) {
        printf("ID: %d, Nama: %s, Tempat Lahir: %s, Tanggal Lahir: %s, Jabatan: %s\n",
               temp->id, temp->name, temp->birthPlace, temp->birthDate, temp->position);
        temp = temp->next;
    }
}

// Fungsi untuk menghapus data karyawan berdasarkan ID
void deleteById(struct Employee** head_ref, int id) {
    struct Employee* temp = *head_ref;
    struct Employee* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("ID Karyawan tidak ditemukan.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Fungsi untuk menghapus semua data karyawan
void deleteAll(struct Employee** head_ref) {
    struct Employee* current = *head_ref;
    struct Employee* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head_ref = NULL;
}

// Fungsi utama
int main() {
    struct Employee* head = NULL;
    int choice, id;
    char name[MAX_NAME], birthPlace[MAX_NAME], birthDate[MAX_NAME], position[MAX_POSITION];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push data karyawan\n");
        printf("2. Tampilkan semua karyawan\n");
        printf("3. Hapus data karyawan berdasarkan ID\n");
        printf("4. Hapus semua data karyawan\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan ID: ");
                scanf("%d", &id);
                if (id > 99999) {
                    printf("ID terlalu panjang (maksimal 5 angka).\n");
                    break;
                }
                printf("Masukkan Nama Lengkap: ");
                scanf(" %[^\n]", name);
                if (strlen(name) > MAX_NAME) {
                    printf("Nama terlalu panjang (maksimal 30 karakter).\n");
                    break;
                }
                printf("Masukkan Tempat Lahir: ");
                scanf(" %[^\n]", birthPlace);
                if (strlen(birthPlace) > MAX_NAME) {
                    printf("Tempat Lahir terlalu panjang (maksimal 30 karakter).\n");
                    break;
                }
                printf("Masukkan Tanggal Lahir: ");
                scanf(" %[^\n]", birthDate);
                printf("Masukkan Jabatan: ");
                scanf(" %[^\n]", position);
                if (strlen(position) > MAX_POSITION) {
                    printf("Jabatan terlalu panjang (maksimal 50 karakter).\n");
                    break;
                }
                push(&head, id, name, birthPlace, birthDate, position);
                break;
            case 2:
                display(head);
                break;
            case 3:
                printf("Masukkan ID yang akan dihapus: ");
                scanf("%d", &id);
                deleteById(&head, id);
                break;
            case 4:
                deleteAll(&head);
                break;
            case 5:
                deleteAll(&head);
                exit(0);
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}
