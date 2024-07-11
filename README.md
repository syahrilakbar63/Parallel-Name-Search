# Parallel Name Search

Proyek ini menggunakan bahasa pemrograman C dan memanfaatkan OpenMP untuk implementasi pencarian paralel dan serial. Program ini membaca daftar nama dan meminta pengguna untuk memasukkan nama yang ingin dicari, dan kemudian menampilkan hasil pencarian serta waktu eksekusi untuk metode pencarian paralel dan serial.

## Cara Penggunaan

1. Clone repository ini:
   ```sh
   git clone https://github.com/syahrilakbar63/Parallel-Name-Search.git
   cd Parallel-Name-Search
   ```

2. Kompilasi program dengan dukungan OpenMP:
   ```sh
   gcc -fopenmp -o parallel_search parallel_search.c
   ```

3. Jalankan program:
   ```sh
   ./parallel_search
   ```

## Lisensi

Proyek ini dilisensikan di bawah Lisensi MIT. Lihat file `LICENSE` untuk informasi lebih lanjut.