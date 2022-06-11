#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

struct data {
    char namaBarang[40], bahanDasar[40], kodeBarang[3];
    int jumlahBarang, hargaBarang;
};

struct data barang[999];
int input;

// Function untuk tambah data
void tambahBarang(void) {

    printf("        --INPUT BARANG--\n\n");
    printf("Banyaknya barang yang akan anda masukkan : ");
    scanf("%d", &input);
    printf("\n");

    for (int i = 0; i < input; i++) {
        printf("::Kode Barang   ::[%d]: ", i + 1);
        scanf(" %[^\n]s", &barang[i].kodeBarang);    
        printf("::Nama Barang   ::[%d]: ", i + 1);
        scanf(" %[^\n]s", &barang[i].namaBarang);    
        printf("::Bahan Dasar   ::[%d]: ", i + 1);
        scanf(" %[^\n]s", &barang[i].bahanDasar);    
        printf("::Jumlah Barang ::[%d]: ", i + 1);
        scanf("%d", &barang[i].jumlahBarang);    
        printf("::Harga Barang  ::[%d]: ", i + 1);
        scanf("%d", &barang[i].hargaBarang);
        printf("\n");    
    }

    printf("Barang berhasil ditambahkan!!");
    sleep(2);
}

// Function untuk menampilkan data
void tampilkanBarang(void) {
    printf("                                       --Persediaan Barang--       \n\n");
    printf("===================================================================================================\n");
    printf("| No  | Kode Barang | Nama Barang          | Bahan Dasar          | Jumlah | Harga Per Unit       |\n");
    printf("===================================================================================================\n");
    for (int i = 0; i < input; i++) {
        printf("| %-3d | %-11s | %-20s | %-20s | %-6d | Rp. %-16d |\n", 
                i + 1, barang[i].kodeBarang, barang[i].namaBarang, barang[i].bahanDasar,
                barang[i].jumlahBarang, barang[i].hargaBarang );
    }

    if (input == 0) {
        printf("|                               Belum ada barang yang ditambahkan                                 |\n");
    }
    printf("===================================================================================================\n");
    printf("\nTekan apa saja untuk kembali ke Menu Utama");
    getch();
}



int main() {
top:
    int menu;
    system("cls");

    printf("    +====================================================+\n");
    printf("    |         TUGAS ARRAY OF STRUCT STRUKTUR DATA        |\n");
    printf("    |      Created by Dimas Firmansyah 2108561035        |\n");
    printf("    +====================================================+\n\n");
    printf("    |                   1. Input Barang                  |  \n");
    printf("    |                   2. Lihat Stok Barang             |  \n");
    printf("    |                   3. Exit                          |  \n\n");
    printf("                      PILIH[1,2,3]: "); 
    scanf("%d", &menu);

    system("cls");

    switch (menu) {
    case 1:
        tambahBarang();
        break;
    case 2:
        tampilkanBarang();
        break;
    case 3:
        printf("Sampai jumpa kembali!!");
        sleep(3);
        return 0;
        break;
    default:
        system("cls");
        printf("Inputan Salah!!");
        sleep(2);
        break;
    }
goto top;
}