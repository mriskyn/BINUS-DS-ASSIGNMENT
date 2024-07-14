#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main() {
    char source_file[100], dest_file[100];
    int fd_source, fd_dest;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Input nama file sumber
    printf("Masukkan nama file sumber: ");
    scanf("%s", source_file);

    // Buka file sumber untuk dibaca
    fd_source = open(source_file, O_RDONLY);
    if (fd_source == -1) {
        perror("Gagal membuka file sumber");
        return EXIT_FAILURE;
    }

    // Input nama file tujuan
    printf("Masukkan nama file tujuan: ");
    scanf("%s", dest_file);

    // Cek apakah file tujuan sudah ada
    fd_dest = open(dest_file, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd_dest == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "File tujuan sudah ada. Proses copy gagal.\n");
        } else {
            perror("Gagal membuat file tujuan");
        }
        close(fd_source);
        return EXIT_FAILURE;
    }

    // Mulai proses copy
    while ((bytes_read = read(fd_source, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(fd_dest, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Gagal menulis ke file tujuan");
            close(fd_source);
            close(fd_dest);
            return EXIT_FAILURE;
        }
    }

    // Tutup file setelah selesai copy
    close(fd_source);
    close(fd_dest);

    printf("File berhasil disalin dari %s ke %s.\n", source_file, dest_file);

    return EXIT_SUCCESS;
}
