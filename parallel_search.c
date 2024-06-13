

#include <stdio.h>  // Untuk fungsi input/output standar
#include <string.h> // Untuk fungsi string seperti strcmp
#include <ctype.h>  // Untuk fungsi konversi karakter seperti tolower
#include <omp.h>    // Untuk fungsi OpenMP

// Fungsi untuk mengubah string menjadi huruf kecil
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Fungsi pencarian linear paralel
int parallel_linear_search(char *arr[], int size, const char *target) {
    int index = -1; // Variabel untuk menyimpan indeks elemen yang ditemukan
    int i;

    // Paralelkan loop for menggunakan OpenMP
    #pragma omp parallel for shared(arr, size, target) private(i)
    for (i = 0; i < size; i++) {
        char lower_arr[100];
        strcpy(lower_arr, arr[i]);
        to_lowercase(lower_arr);

        if (strcmp(lower_arr, target) == 0) { // Bandingkan elemen dengan target
            #pragma omp critical // Seksi kritis untuk mencegah kondisi balapan
            {
                if (index == -1 || i < index) {
                    index = i; // Update indeks elemen yang ditemukan
                }
            }
        }
    }

    return index; // Kembalikan indeks elemen yang ditemukan atau -1 jika tidak ditemukan
}

int main() {
    // Daftar nama yang akan dicari
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
    int size = sizeof(arr) / sizeof(arr[0]); // Hitung ukuran array
    char target[100];    // Buffer untuk nama yang akan dicari

    // Ambil input nama yang akan dicari dari terminal
    printf("\nMasukkan nama di kelas B yang akan dicari: ");
    fgets(target, 100, stdin);
    target[strcspn(target, "\n")] = 0; // Hilangkan newline di akhir input
    to_lowercase(target); // Ubah target menjadi huruf kecil

    // Cetak daftar nama
    printf("\nDaftar Nama Kelas B:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: %s\n", i, arr[i]);
    }

    // Panggil fungsi pencarian paralel
    int index = parallel_linear_search(arr, size, target);

    // Tampilkan hasil pencarian
    if (index != -1) {
        printf("\nNama '%s' ditemukan pada indeks %d\n", arr[index], index); // Elemen ditemukan
    } else {
        printf("\nNama '%s' tidak ditemukan dalam daftar nama di kelas B\n", target);   // Elemen tidak ditemukan
    }

    return 0;
}