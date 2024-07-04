#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <omp.h>

// Fungsi untuk mengubah string menjadi huruf kecil
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Fungsi pencarian linear paralel
int parallel_linear_search(char **arr, int size, const char *target) {
    int index = -1;
    int i;

    #pragma omp parallel for shared(arr, size, target) private(i)
    for (i = 0; i < size; i++) {
        char lower_arr[100];
        strcpy(lower_arr, arr[i]);
        to_lowercase(lower_arr);

        if (strcmp(lower_arr, target) == 0) {
            #pragma omp critical
            {
                if (index == -1 || i < index) {
                    index = i;
                }
            }
        }
    }

    return index;
}

// Fungsi pencarian linear serial
int serial_linear_search(char **arr, int size, const char *target) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        char lower_arr[100];
        strcpy(lower_arr, arr[i]);
        to_lowercase(lower_arr);

        if (strcmp(lower_arr, target) == 0) {
            index = i;
            break; // Hentikan pencarian setelah ditemukan
        }
    }
    return index;
}

// Fungsi untuk membaca data dari file CSV
int read_csv(const char *filename, char **arr, int max_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Gagal membuka file");
        return -1;
    }

    char line[256];
    int index = 0;

    while (fgets(line, sizeof(line), file) && index < max_size) {
        // Hapus newline di akhir baris
        line[strcspn(line, "\n")] = 0;
        arr[index] = strdup(line);
        index++;
    }

    fclose(file);
    return index;
}

int main() {
    const char *filename = "data.csv";
    const int max_size = 100000; // Kapasitas array
    char **arr = (char **)malloc(max_size * sizeof(char *));
    int size = read_csv(filename, arr, max_size);

    if (size == -1) {
        free(arr);
        return 1;
    }

    char target[100];

    printf("\nMasukkan nama di kelas B yang akan dicari: ");
    fgets(target, 100, stdin);
    target[strcspn(target, "\n")] = 0;
    to_lowercase(target);

    printf("\nTarget (lowercase): '%s'\n", target);  // Debug output

    // Ukur waktu pencarian paralel
    double start_parallel = omp_get_wtime();
    int index_parallel = parallel_linear_search(arr, size, target);
    double end_parallel = omp_get_wtime();

    // Ukur waktu pencarian serial
    double start_serial = omp_get_wtime();
    int index_serial = serial_linear_search(arr, size, target);
    double end_serial = omp_get_wtime();

    // Tampilkan hasil pencarian
    if (index_parallel != -1) {
        printf("\nNama '%s' ditemukan pada indeks %d (paralel)\n", arr[index_parallel], index_parallel);
    } else {
        printf("\nNama '%s' tidak ditemukan dalam daftar nama di kelas B (paralel)\n", target);
    }

    if (index_serial != -1) {
        printf("Nama '%s' ditemukan pada indeks %d (serial)\n", arr[index_serial], index_serial);
    } else {
        printf("Nama '%s' tidak ditemukan dalam daftar nama di kelas B (serial)\n", target);
    }

    // Tampilkan waktu eksekusi
    printf("\nWaktu eksekusi paralel: %f detik\n", end_parallel - start_parallel);
    printf("Waktu eksekusi serial: %f detik\n", end_serial - start_serial);

    // Bebaskan memori yang dialokasikan
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
