#include <stdio.h>
#include <stdlib.h>

// Buat struktur dari node dengan elemen node int bilangan dan pointer yang akan menunjuk ke node selanjutnya
struct tnode
{
    int bil;
    struct tnode *next;
};

// Fungsi untuk mengecek apakah linked list kosong atau berisi
int isEmpty(struct tnode *tail)
{
    if(tail == NULL) return 1;
    else return 0;
}

// Dekorasi
void header()
{
    printf("====================================================\n");
    printf("                Program Linked List                 \n");
    printf("====================================================\n\n");
}

// Dekorasi
void footer()
{
    printf("\n==================================================\n");
    printf("                    Terima Kasih                    \n");
    printf("====================================================\n\n");
}

//Fungsi yang digunakan untuk mencetak node - node yang ada, jika ada
void lihat(struct tnode *head)
{
    system("cls");
    struct tnode *cetak;
    cetak = head;
    printf("======================================================\n");
    printf("                Menampilkan Data Antrian              \n");
    printf("======================================================\n");
    while(cetak != NULL){
        printf("Bilangan: %d\n", cetak->bil);
        cetak = cetak->next;
    }
}

// Fungsi yang berisi menu yang dapat digunakan user
void menu()
{
    int pilMenu, konfirmasi;
    struct tnode *head, *tail, *node, *baru, *cetak;
    baru = head = NULL;
    tail = NULL;
    do{
        header();
        printf("Menu : \n\n");
        printf("1. Tambah Bilangan\n2. Hapus Bilangan\n3. Lihat Bilangan\n4. Keluar\n\n");
        printf("Pilih Menu : ");
        scanf("%d", &pilMenu);
        fflush(stdin);
        switch(pilMenu)
        {
            case 1:
                {
                    system("cls");
                    header();
                    node = (struct tnode*)malloc(sizeof(struct tnode));
                    printf("Ketik Bilangan     : ");
                    scanf("%d", &node->bil);
                    baru = node;
                    baru->next = NULL;
                    if(isEmpty(tail) == 1){
                        head = baru;
                        tail = baru;
                        tail->next = NULL;
                    }
                    else{
                        tail->next = baru;
                        tail = baru;
                    }
                    printf("Bilangan %d berhasil ditambahkan\n", baru->bil);
                    break;
                }
            case 2:
                {
                    system("cls");
                    if(isEmpty(tail) == 1)
                        printf("\nMaaf! Linked list masih kosong\n\n");
                    else{
                        printf("Apakah anda yakin ingin menghapus bilangan %d?", head->bil);
                        printf("Ketik (1) jika iya : ");
                        scanf("%d", &konfirmasi);
                        if(konfirmasi == 1){
                            if(head != tail){
                                head=head->next;
						        printf("\n\nBilangan %d berhasil dihapus!\n", cetak->bil);
                            }
                            else{
                                printf("\n\nBilangan %d berhasil dihapus!\n", cetak->bil);
                                head = tail = NULL;
                            }
                            cetak = head;
                        }
                        else
                            printf("\nProses dibatalkan\n\n");
                    }
                    break;
                }
            case 3:
                {
                    system("cls");
                    cetak = head;
                    if(isEmpty(tail) == 1)
                        printf("\nMaaf! Linked list masih kosong\n\n");
                    else
                        lihat(head);
                    break;
                }
            default:
                system("cls");
                printf("Maaf! Pilihan menu tidak sesuai!\n");
        }
    }while(pilMenu != 4);
}

// Fungsi utama yang akan memanggil fungsi menu

int main()
{
    menu();
    system("cls");
    footer();
    return 0;
}