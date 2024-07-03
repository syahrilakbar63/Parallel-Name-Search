#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <omp.h>

// Fungsi untuk mengubah string menjadi huruf kecil
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Fungsi pencarian linear paralel
int parallel_linear_search(char *arr[], int size, const char *target) {
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
int serial_linear_search(char *arr[], int size, const char *target) {
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

int main() {
    char *arr[] = {
        "NUR ALAM",
        "SASTRA CHANDRA KIRANA",
        "SYAHRIL AKBAR",
        "JIHAN IZZATHUL MUJIDAH",
        "FARID KUSUMA WARDANA",
        "ARNETA",
        "RESKI ANUGRAH SARI",
        "MAKMUR JAYA NUR",
        "MUHAMMAD ASYGAR FAERUDDIN",
        "MUH RISWAN",
        "RISAL",
        "ROMADHAN",
        "MUH AL IQRAM MARZAH",
        "SARINA",
        "SONY ACHMAD DJALIL",
        "ANUGRAH RESKY SAMUDRA R",
        "RIZKY MAULIA",
        "RIZKY JUNI SETIAWAN",
        "MUHAMMAD ADIL SYAPUTRA",
        "GEMPAR PERKASA TAHIR",
        "ISMI SARIF",
        "NUR ANNISA SYARIFUDDIN",
        "MUH ULIL AMRI",
        "ULUL AZMI",
        "RIFATUL JAMILA"
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    char target[100];

    printf("\nMasukkan nama di kelas B yang akan dicari: ");
    fgets(target, 100, stdin);
    target[strcspn(target, "\n")] = 0;
    to_lowercase(target);

    printf("\nDaftar Nama Kelas B:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: %s\n", i, arr[i]);
    }

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

    return 0;
}
