# Parallel Name Search

Parallel Name Search adalah program C yang menggunakan pencarian linear secara paralel dengan bantuan OpenMP untuk mencari nama dalam daftar yang diberikan. Program ini mengambil input nama dari pengguna melalui terminal dan melakukan pencarian. Program ini dirancang untuk menunjukkan penggunaan dasar OpenMP dalam memparallelkan operasi pencarian.

## Cara Penggunaan

1. Clone repository ini:
   ```sh
   git clone https://github.com/syahrilakbar63/Parallel-Name-Search.git
   cd Parallel_Name_Search
   ```

2. Kompilasi program dengan dukungan OpenMP:
   ```sh
   gcc -fopenmp -o parallel_search parallel_search.c
   ```

3. Jalankan program:
   ```sh
   ./parallel_search
   ```

## Contoh Output

```
Masukkan nama di kelas B yang akan dicari: syahril akbar

Daftar Nama Kelas B:
0: NUR ALAM
1: SASTRA CHANDRA KIRANA
2: SYAHRIL AKBAR
...

Nama 'SYAHRIL AKBAR' ditemukan pada indeks 2
```

## Lisensi

Proyek ini dilisensikan di bawah Lisensi MIT. Lihat file `LICENSE` untuk informasi lebih lanjut.