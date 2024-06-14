#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char id[50];
    char nama[100];
    int stok;
    float harga;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} DoublyLinkedList;

Node* createNode(char* id, char* nama, int stok, float harga) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->id, id);
    strcpy(newNode->nama, nama);
    newNode->stok = stok;
    newNode->harga = harga;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void addToEnd(DoublyLinkedList* list, char* id, char* nama, int stok, float harga) {
    Node* newNode = createNode(id, nama, stok, harga);
    if (!list->head) {
        list->head = newNode;
        return;
    }
    Node* last = list->head;
    while (last->next) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

void deleteNode(DoublyLinkedList* list, char* id) {
    Node* temp = list->head;
    while (temp) {
        if (strcmp(temp->id, id) == 0) {
            if (temp->prev) {
                temp->prev->next = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            if (temp == list->head) {
                list->head = temp->next;
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

Node* search(DoublyLinkedList* list, char* id) {
    Node* temp = list->head;
    while (temp) {
        if (strcmp(temp->id, id) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void updateNode(DoublyLinkedList* list, char* id, char* nama, int stok, float harga) {
    Node* temp = search(list, id);
    if (temp) {
        if (nama) strcpy(temp->nama, nama);
        if (stok >= 0) temp->stok = stok;
        if (harga >= 0) temp->harga = harga;
    }
}

void display(DoublyLinkedList* list) {
    Node* temp = list->head;
    if (!temp) {
        printf("Tidak ada barang dalam stok.\n");
        return;
    }

    printf("+--------------------------------------------------------------+\n");
    printf("| %-10s | %-20s | %-10s | %-10s |\n", "ID", "Nama Barang", "Stok", "Harga");
    printf("+--------------------------------------------------------------+\n");

    while (temp) {
        printf("| %-10s | %-20s | %-10d | %-10.2f |\n", temp->id, temp->nama, temp->stok, temp->harga);
        temp = temp->next;
    }

    printf("+--------------------------------------------------------------+\n");
}

void menu() {
  DoublyLinkedList list;
  list.head = NULL;

  while (1) {
      printf("\nMenu:\n");
      printf("1. Tambahkan Barang Baru\n");
      printf("2. Kurangi Stok Barang\n");
      printf("3. Perbarui Informasi Barang\n");
      printf("4. Cari Barang\n");
      printf("5. Tampilkan Semua Barang\n");
      printf("6. Hapus Barang\n");
      printf("7. Keluar\n");
      printf("Pilih menu: ");

      int choice;
      scanf("%d", &choice);
      getchar(); // to consume newline character after number input

      if (choice == 1) {
          char id[50], nama[100];
          int stok;
          float harga;
          printf("Masukkan ID Barang: ");
          fgets(id, 50, stdin);
          id[strcspn(id, "\n")] = 0; // Remove trailing newline
          printf("Masukkan Nama Barang: ");
          fgets(nama, 100, stdin);
          nama[strcspn(nama, "\n")] = 0; // Remove trailing newline
          printf("Masukkan Jumlah Stok: ");
          scanf("%d", &stok);
          printf("Masukkan Harga Barang: ");
          scanf("%f", &harga);
          addToEnd(&list, id, nama, stok, harga);
          printf("Barang berhasil ditambahkan!\n");

      } else if (choice == 2) {
          char id[50];
          int jumlah;
          printf("Masukkan ID Barang yang Stoknya Ingin Dikurangi: ");
          fgets(id, 50, stdin);
          id[strcspn(id, "\n")] = 0; // Remove trailing newline
          printf("Masukkan Jumlah yang Dikurangi: ");
          scanf("%d", &jumlah);
          Node* barang = search(&list, id);
          if (barang) {
              if (barang->stok >= jumlah) {
                  barang->stok -= jumlah;
                  printf("Stok berhasil dikurangi!\n");
              } else {
                  printf("Stok tidak mencukupi!\n");
              }
          } else {
              printf("Barang tidak ditemukan!\n");
          }

      } else if (choice == 3) {
          char id[50], nama[100];
          int stok;
          float harga;
          printf("Masukkan ID Barang yang Ingin Diperbarui: ");
          fgets(id, 50, stdin);
          id[strcspn(id, "\n")] = 0; // Remove trailing newline
          printf("Masukkan Nama Barang Baru (kosongkan jika tidak berubah): ");
          fgets(nama, 100, stdin);
          nama[strcspn(nama, "\n")] = 0; // Remove trailing newline
          printf("Masukkan Jumlah Stok Baru (-1 jika tidak berubah): ");
          scanf("%d", &stok);
          printf("Masukkan Harga Baru (-1 jika tidak berubah): ");
          scanf("%f", &harga);
          updateNode(&list, id, (strlen(nama) > 0) ? nama : NULL, (stok >= 0) ? stok : -1, (harga >= 0) ? harga : -1);
          printf("Informasi barang berhasil diperbarui!\n");

      } else if (choice == 4) {
          char id[50];
          printf("Masukkan ID Barang yang Dicari: ");
          fgets(id, 50, stdin);
          id[strcspn(id, "\n")] = 0; // Remove trailing newline
          Node* barang = search(&list, id);
          if (barang) {
              printf("Barang Ditemukan: ID: %s, Nama: %s, Stok: %d, Harga: %.2f\n", barang->id, barang->nama, barang->stok, barang->harga);
          } else {
              printf("Barang tidak ditemukan!\n");
          }

      } else if (choice == 5) {
          display(&list);
      } else if (choice == 6) {
          char id[50];
          printf("Masukkan ID Barang yang Ingin Dihapus: ");
          fgets(id, 50, stdin);
          id[strcspn(id, "\n")] = 0; // Remove trailing newline
          deleteNode(&list, id);
          printf("Barang berhasil dihapus!\n");

      } else if (choice == 7) {
          printf("Terima kasih!\n");
          break;

      } else {
          printf("Pilihan tidak valid!\n");
      }
  }
}

int main() {
  menu();
  return 0;
}
