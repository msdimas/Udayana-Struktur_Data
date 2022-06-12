#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define LIMIT 1000 // Jumlah maksimal top stack
#define JML_PECAHAN 4 //Jumlah pecahan yang akan dibuat
#define USER_MAX 3 //Jumlah user yang bisa login

// implementasi ADT
typedef char string[512]; // string

typedef struct { // struktur data untuk menyimpan data user
    int norek;
    int pin;
    double saldo;
}User;

typedef struct { // struktur data untuk menyimpan data stack
    int data[LIMIT];
    int top;
    int nominal;
    string nominalStr;
}Stack;

typedef struct { // struktur data untuk menyimpan data queue
    User data[LIMIT];
    int front;
    int rear;
}Queue;

// ADT node untuk buat Binary tree
struct node { // struktur data untuk menyimpan data node
    int value;
    struct node* left_child, * right_child;
};

struct node* new_node(int value) { //struct yang digunakan untuk node baru
    struct node* tmp = (struct node*)malloc(sizeof(struct node)); //untuk mengalokasikan memori baru ke struct node
    tmp->value = value; //mengisi value
    tmp->left_child = tmp->right_child = NULL; //mengisi pointer kosong
    return tmp; //mengembalikan pointer
}

void print_tree(struct node* root_node) { // Menampilkan binary tree
    if (root_node != NULL) { //jika root_node tidak kosong
        print_tree(root_node->left_child); //mengembalikan ke node kiri
        printf("%d \n", root_node->value); //menampilkan value
        print_tree(root_node->right_child); //mengembalikan ke node kanan
    }
}

struct node* insert_node(struct node* node, int value) // Masukkan data ke Binary tree
{
    if (node == NULL) return new_node(value); //jika node kosong, maka return new_node
    if (value < node->value) { //jika value lebih kecil dari node->value
        node->left_child = insert_node(node->left_child, value); //maka taruh di node kiri
    } else if (value > node->value) { //jika value lebih besar dari node->value
        node->right_child = insert_node(node->right_child, value); //maka taruh di node kanan
    } return node; //mengembalikan node
}

// deklarasi variabel bertipe ADT
User user[USER_MAX]; //array user
Stack pecahan[4]; //array of stack
Queue antrian; //untuk menampung antrian
struct node* root_node = NULL; //pointer root node

// fitur User
int login(); //fungsi login
void setor(User* asal); //fungsi setor
void transfer(User* asal); //fungsi transfer
void tarik(User* asal); //fungsi tarik
double cek_saldo(User asal); //fungsi cek saldo
void keluar(); //fungsi keluar
int search(User cari); // implementasi searching, cari User ada atau tidak

// fungsi stack
void push(Stack* stack); //fungsi push atau menambah stack
void pop(Stack* stack); //fungsi pop atau meghapus stack
int size(Stack stack); //fungsi size atau menghitung jumlah stack
void view_pecahan();  // fungsi untuk lihat daftar pecahan dengan sorting (Bubble sort)

// fungsi queue
void insert(Queue* q, User u); //fungsi insert atau menambahkan antrian
void delete(Queue* q); //fungsi delete atau menghapus antrian

void set_data() { //fungsi untuk mengisi data user

    // set data user dalam array user
    user[0].norek = 10001;
    user[0].pin = 1111;
    user[0].saldo = 10000000;

    user[1].norek = 10002;
    user[1].pin = 1122;
    user[1].saldo = 5000000;

    user[2].norek = 10003;
    user[2].pin = 1133;
    user[2].saldo = 7500000;

    // set data nomor rekening ke binary tree
    root_node = insert_node(root_node, user[0].norek); //insert ke binary tree
    insert_node(root_node, user[1].norek); //insert ke binary tree
    insert_node(root_node, user[2].norek); //insert ke binary tree


    // set data antrian user
    antrian.front = antrian.rear = -1; //menginisialisasi antrian ke -1
    insert(&antrian, user[0]); //insert user ke antrian
    insert(&antrian, user[1]); //insert user ke antrian
    insert(&antrian, user[2]); //insert user ke antrian


    // set semua lembar pecahan menjadi kosong dulu
    for (int i = 0; i < JML_PECAHAN; i++) //looping untuk mengisi semua pecahan
        pecahan[i].top = -1; //menginisialisasi semua pecahan menjadi kosong

    // memasukan 100 lembar ke setiap pecahan
    for (int i = 0; i < JML_PECAHAN; i++) { //looping untuk mengisi semua pecahan
        for (int j = 0; j < 100; j++) { //looping untuk mengisi 100 lembar
            push(&pecahan[i]); //push ke stack
        }
    }

    // set nominal pecahan
    pecahan[0].nominal = 100000;
    strcpy(pecahan[0].nominalStr, "100rb"); //mengisi string nominal pecahan

    pecahan[1].nominal = 75000;
    strcpy(pecahan[1].nominalStr, "75rb"); //mengisi string nominal pecahan

    pecahan[2].nominal = 50000;
    strcpy(pecahan[2].nominalStr, "50rb"); //mengisi string nominal pecahan

    pecahan[3].nominal = 20000;
    strcpy(pecahan[3].nominalStr, "20rb"); //mengisi string nominal pecahan
}

int main() { //main program
    system("cls");
    set_data(); //mengisi data user dan pecahan

    while (!isEmpty(&antrian)) { //jika antrian tidak kosong
        int pilihan; //variabel pilihan

        printf("\n=================================\n");
        printf("+ Selamat datang di Mesin ATM. + \n");  // Cetak Menu Login
        printf("=================================\n");
        printf("No. Antrian: %d\n", antrian.front + 1);     // nomor antrian diambil dari user terdepan di antrian (queue)
        printf("1. Masukkan ATM\n");
        printf("2. Lihat daftar user\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) { //jika pilihan 1
            // Login dulu
            login(antrian.data[antrian.front]); //login user terdepan di antrian
        }
        else if (pilihan == 2) { //jika pilihan 2
            printf("Daftar nomor rekening user:\n"); //cetak daftar nomor rekening user
            print_tree(root_node); //cetak daftar nomor rekening user
            continue; //lanjut ke menu utama
        }
        else {
            delete(&antrian); //jika pilihan 3 (Atau selain 1, 2), maka delete user terdepan di antrian
            continue; //lanjut ke menu utama
        }

        // menu
        int flag = 1; //flag untuk menentukan apakah user ingin keluar atau tidak
        while (flag == 1) {
            int pilihan;
            printf("\n\nSilakan pilih menu transaksi:\n");
            printf("1. Setor tunai\n2. Tarik tunai\n3. Transfer\n4. Cek saldo\n5. Selesai transaksi\n");
            printf("Pilihan anda: ");
            scanf("%d", &pilihan);
            switch (pilihan) {
            case 1: //jika pilihan 1
                setor(&antrian.data[antrian.front]); //jalankan fungsi setor
                break;
            case 2: //jika pilihan 2
                tarik(&antrian.data[antrian.front]); //jalankan fungsi tarik
                break;
            case 3: //jika pilihan 3
                transfer(&antrian.data[antrian.front]); //jalankan fungsi transfer
                break;
            case 4: //jika pilihan 4
                printf("Saldo anda: Rp%.f", cek_saldo(antrian.data[antrian.front])); //jalankan fungsi cek saldo
                break;
            case 5: //jika pilihan 5
                flag = 0;//jika pilihan 5, maka keluar dari menu
                break;
            default:
                break;
            }
        }
    }

    printf("\nSelesai..."); //jika antrian kosong, maka cetak selesai
    return 0;
}

void push(Stack* stack) { //fungsi push
    int data = 1; //variabel data bernilai 1
    if (stack->top == LIMIT - 1) {    // jika pointer sudah di paling atas
        printf("Tumpukan sudah penuh\n"); //cetak tumpukan penuh
    }
    else { //jika belum penuh
        stack->top++;  // tambah tumpukan pecahan
        stack->data[stack->top] = data;   // masukkan tumpukan lembaran baru
    }
}

void pop(Stack* stack) { //fungsi pop
    stack->top--; // hapus tumpukan paling atas
}

int size(Stack stack) { //fungsi size
    return stack.top + 1;    // print jumlah lembar pecahan
}

void insert(Queue* q, User u) { //fungsi insert
    if (q->rear == LIMIT - 1) {         // jika antrian terakhir telah mencapai LIMIT
        printf("Antrian sudah penuh.\n"); //cetak antrian penuh
    }
    else { //jika belum penuh
        if (q->front == -1) {       // jika antrian masing kosong
            q->front = 0;           // jadikan antrian yang pertama
        }
        q->rear++;              // rear dari q akan di increment
        q->data[q->rear] = u;   // insert data ke antrian paling belakang
    }
}

void delete(Queue* q) { //fungsi delete
    if (isEmpty(q)) {       // cek apakah sudah kosong
        printf("Antrian sudah kosong.\n"); //cetak antrian kosong
    }
    else { //jika belum kosong
        q->front++;     // majukan antrian (yang pertama keluar)
    }
}

int isEmpty(Queue* q) { //fungsi isEmpty
    if (q->front == -1 || q->front > q->rear) {     // jika tidak ada data di antrian terdepan
        return 1; //return 1 (true)
    } //jika ada data di antrian terdepan
    return 0; //return 0 (false)
}

int login(User u) { //fungsi login
    int norek; //variabel norek
    int pin, coba = 1; //variabel pin dan coba (percobaan login)

    while (coba <= 3) {     // Jika Percobaan loginnya masih dibawah 3x, maka tampilkan menu yang diwah!
        printf("Nomor rekening: %d\n", user->norek);
        printf("Masukkan PIN Anda:\n");
        printf("PIN: ");
        scanf("%d", &pin); // setelah pin dimasukkan

        if (u.pin == pin) {  // cek keseuaian PIN yang di input
            return 1; // jika sesuai return 1 (true)
        }

        printf("Gagal. Silakan coba lagi.\n"); //jika tidak sesuai, maka coba lagi
        coba++;  // increase jumlah percobaan
    } //jika percobaan sudah 3x, maka return 0 (false)
    return 0;
}

int search(User cari) { //fungsi search
    for (int i = 0; i < USER_MAX; i++) {     // implementasi searching menggunakan (linear search)
        if (cari.norek == user[i].norek) {   // cari nomor rekening di dalam array 1 per satu
            return i;  // jika ketemu kembalian nomor index nya
        }
    } //jika tidak ketemu, maka return -1 (false)
    return -1;
}

void view_pecahan() { //fungsi view pecahan
    // disini ada proses bubble sort
    for (int i = 0; i < JML_PECAHAN - 1; i++) { //bubble sort
        for (int j = 0; j < JML_PECAHAN - i - 1; j++) { //bubble sort
            if (size(pecahan[j]) < size(pecahan[j + 1])) {   // jika nilai jumlah pecahan sebelah kiri lebih kecil, maka tukar ke sebelah kanan
                Stack temp = pecahan[j]; //tukar
                pecahan[j] = pecahan[j + 1]; //tukar
                pecahan[j + 1] = temp; //tukar
            }
        }
    }

    // print daftar pecahan setelah di sorting
    printf("Lembar pecahan:\n");
    for (int i = 0; i < JML_PECAHAN; i++) { //print
        printf("%d. %s - %d lembar\n", (i + 1), pecahan[i].nominalStr, size(pecahan[i]));
    }
}

double cek_saldo(User asal) { //fungsi cek saldo
    return asal.saldo; //return saldo
}

void transfer(User* asal) { //fungsi transfer
    User tujuan; //variabel tujuan
    int norek_tujuan; //variabel norek tujuan
    double nominal; //variabel nominal

    printf("Nomor rekening tujuan: "); //input nomor rekening tujuan
    scanf("%d", &norek_tujuan); //input nomor rekening tujuan
    tujuan.norek = norek_tujuan; //set nomor rekening tujuan

    int index_tujuan = search(tujuan);  // ambil index nomor rekening tujuan pada array user global

    if (index_tujuan >= 0) { //jika norek ketemu
        printf("Masukkan nominal: "); //input nominal
        scanf("%lf", &nominal); //setelah input nominal

        if (nominal < asal->saldo) {   // cek jika saldo mencukupi
            user[index_tujuan].saldo += nominal; //tambah saldo tujuan
            asal->saldo -= nominal; //kurangi saldo asal
            printf("Transaksi berhasil.\n"); //cetak transaksi berhasil
        } else //jika saldo tidak cukup
            printf("Saldo tidak cukup");
    } else //jika no rek tidak ketemu
        printf("Nomor rekening tidak ditemukan.\n");
}


void setor(User* asal) { //fungsi setor
    int pilihan, jml_lembar; //variabel pilihan dan jumlah lembar
    view_pecahan();     // tampilkan daftar pecahan

    printf("Pilih: ");
    scanf("%d", &pilihan); //input pilihan

    printf("Masukkan jumlah lembar kertas: ");
    scanf("%d", &jml_lembar); //input jumlah lembar

    if (pilihan >= 1 && pilihan <= 4) {     // cek apakah pilihan valid (1-4) jika iya,
        pilihan--; // kurangi nilai dari pilihan 1 karena array dimulai dari 0
        if (size(pecahan[pilihan]) + jml_lembar <= LIMIT) { // cek apakah masih dibawah LIMIT
            for (int i = 0; i < jml_lembar; i++) //loop untuk menambahkan lembar ke array
                push(&pecahan[pilihan]); //push lembar ke array

            asal->saldo += pecahan[pilihan].nominal * jml_lembar; //tambah saldo asal sesuai dengan jumlah lembar yang ditambahkan
            printf("Transaksi berhasil.\n"); //cetak transaksi berhasil
        } else { //jika tidak dibawah LIMIT
            printf("Transaksi gagal. Cakupan lembaran mencapai LIMIT\n");
        }
    } else { //jika pilihan tidak valid
        printf("Pilihan tidak valid.\n");
    }
}

void tarik(User* asal) { //fungsi tarik
    int pilihan, jml_lembar;//variabel pilihan dan jumlah lembar
    view_pecahan(); // tampilkan daftar pecahan

    printf("Pilih: ");
    scanf("%d", &pilihan); //input pilihan

    printf("Masukkan jumlah lembar kertas: ");
    scanf("%d", &jml_lembar); //input jumlah lembar

    double total = 0; //variabel total set ke 0

    if (pilihan >= 1 && pilihan <= 4) {     // cek apakah pilihan valid (1-4)
        pilihan--; // kurangi nilai dari pilihan 1 karena array dimulai dari 0
        total = pecahan[pilihan].nominal * jml_lembar; //hitung total nominal yang akan ditarik
        if (total <= asal->saldo) {  // jika jumlah tarik tunai tidak melebihi saldo di User.
            if (jml_lembar <= size(pecahan[pilihan])) { // jika jumlah lembar tidak melebihi sisa lembar yang ada.
                asal->saldo -= total; //kurangi saldo asal
                for (int i = 0; i < jml_lembar; i++) //loop untuk mengurangi lembar dari array
                    pop(&pecahan[pilihan]); //pop lembar dari array

                printf("Transaksi berhasil.\n"); //cetak transaksi berhasil
            } else { //jika jumlah lembar melebihi sisa lembar yang ada
                printf("Transaksi gagal. Lembaran pecahan tidak mencukupi.\n");
            }
        } else { //jika jumlah tarik tunai melebihi saldo di User
            printf("Transaksi gagal. Saldo tidak mencukupi.\n");
        }
    }
}
