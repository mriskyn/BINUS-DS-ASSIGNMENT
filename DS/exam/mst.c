#include <stdio.h>
#include <stdlib.h>

// Struktur untuk merepresentasikan sebuah edge dalam graph
struct Edge {
    int src, dest, weight;
};

// Struktur untuk merepresentasikan sebuah subset untuk Union-Find
struct Subset {
    int parent;
    int rank;
};

// Fungsi untuk menemukan subset dari elemen i
int find(struct Subset subsets[], int i) {
    // menemukan root dan melakukan path compression
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Fungsi untuk melakukan union dua subset x dan y
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach tree dengan rank lebih rendah ke tree dengan rank lebih tinggi
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // Jika ranks sama, jadikan salah satu root dan tingkatkan rank-nya
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Fungsi pembanding untuk qsort() berdasarkan weight
int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight > edgeB->weight;
}

// Fungsi utama untuk mengimplementasikan algoritma Kruskal
void KruskalMST(struct Edge edges[], int V, int E) {
    struct Edge result[V];  // Array untuk menyimpan MST
    int e = 0;  // Indeks untuk result[]
    int i = 0;  // Indeks untuk edge yang dipilih selanjutnya

    // Mengurutkan semua edge berdasarkan weight
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    // Alokasikan memori untuk membuat subset V
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Membuat subset sebagai pohon tunggal
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Jumlah edge yang dipilih harus V-1
    while (e < V - 1 && i < E) {
        // Pilih edge dengan weight terkecil
        struct Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // Jika tidak menyebabkan siklus, masukkan dalam hasil
        if (x != y) {
            result[e++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    // Cetak hasil
    printf("Edge dalam MST dengan panjang minimal:\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d km\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

int main() {
    // Jumlah node (Data Center, Kantor1, Kantor2, Pemukiman1, Pemukiman2)
    int V = 5;

    // Jumlah edge berdasarkan studi kasus
    int E = 7;

    // Inisialisasi edges berdasarkan tabel yang diberikan
    struct Edge edges[] = {
        {0, 1, 30}, // Data center - Kantor1
        {0, 2, 20}, // Data center - Kantor2
        {0, 3, 10}, // Data center - Pemukiman1
        {1, 3, 5},  // Kantor1 - Pemukiman1
        {1, 4, 25}, // Kantor1 - Pemukiman2
        {2, 3, 13}, // Kantor2 - Pemukiman1
        {2, 4, 40}  // Kantor2 - Pemukiman2
    };

    KruskalMST(edges, V, E);

    return 0;
}
