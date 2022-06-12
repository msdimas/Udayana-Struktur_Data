#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define LIMIT 1000
#define JML_PECAHAN 4
#define USER_MAX 3

// implementasi ADT
typedef char string[512];

typedef struct {
    int norek;
    int pin;
    double saldo;
}User;

typedef struct {
    int data[LIMIT];
    int top;
    int nominal;
    string nominalStr;
}Stack;

typedef struct {
    User* data[LIMIT];
    int front;
    int rear;
}Queue;

// ADT node untuk buat Binary tree
struct node
{
    int value;
    struct node* left_child, * right_child;
};
struct node* new_node(int value)
{
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    tmp->value = value;
    tmp->left_child = tmp->right_child = NULL;
    return tmp;
}
void print_tree(struct node* root_node) // Menampilkan binary tree
{
    if (root_node != NULL)
    {
        print_tree(root_node->left_child);
        printf("%d \n", root_node->value);
        print_tree(root_node->right_child);
    }
}
struct node* insert_node(struct node* node, int value) // Masukkan data ke Binary tree
{
    if (node == NULL) return new_node(value);
    if (value < node->value)
    {
        node->left_child = insert_node(node->left_child, value);
    }
    else if (value > node->value)
    {
        node->right_child = insert_node(node->right_child, value);
    }
    return node;
}

// deklarasi variabel bertipe ADT
User user[USER_MAX];
Stack pecahan[4];
Queue antrian;
struct node* root_node = NULL;      // root binary tree

// fitur User
int login();
void setor(User* asal);
void transfer(User* asal);
void tarik(User* asal);
double cek_saldo(User* asal);
void keluar();
int search(User cari); // implementasi searching, cari User ada atau tidak

// fungsi stack
void push(Stack* stack);
void pop(Stack* stack);
int size(Stack stack);
void view_pecahan();    // fungsi untuk lihat daftar pecahan dengan sorting (Bubble sort)

// fungsi queue
void insert(Queue* q, User* u);
void delete(Queue* q);

void set_data() {

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
    root_node = insert_node(root_node, user[0].norek);
    insert_node(root_node, user[1].norek);
    insert_node(root_node, user[2].norek);


    // set data antrian user 
    antrian.front = antrian.rear = -1;
    insert(&antrian, &user[0]);
    insert(&antrian, &user[1]);
    insert(&antrian, &user[2]);


    // set semua lembar pecahan menjadi kosong dulu
    for (int i = 0; i < JML_PECAHAN; i++)
        pecahan[i].top = -1;

    // memasukan 100 lembar ke setiap pecahan
    for (int i = 0; i < JML_PECAHAN; i++) {
        for (int j = 0; j < 100; j++) {
            push(&pecahan[i]);
        }
    }

    // set nominal pecahan
    pecahan[0].nominal = 100000;
    strcpy(pecahan[0].nominalStr, "100rb");

    pecahan[1].nominal = 75000;
    strcpy(pecahan[1].nominalStr, "75rb");

    pecahan[2].nominal = 50000;
    strcpy(pecahan[2].nominalStr, "50rb");

    pecahan[3].nominal = 20000;
    strcpy(pecahan[3].nominalStr, "20rb");
}

int main() {
    // system("cls");
    set_data();

    while (!isEmpty(&antrian)) {
        int pilihan;

        printf("\n=================================\n");
        printf("+ Selamat datang di Mesin ATM. + \n");
        printf("=================================\n");

        printf("No. Antrian: %d\n", antrian.front + 1);     // nomor antrian diambil dari user terdepan di antrian (queue)
        printf("1. Masukkan ATM\n");
        printf("2. Lihat daftar user\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            // Login dulu
            int flag = login(*antrian.data[antrian.front]);
            if (flag == -1) {       // gagal login
                continue;
            }
        }
        else if (pilihan == 2) {
            printf("Daftar nomor rekening user:\n");
            print_tree(root_node);
            continue;
        }
        else {
            delete(&antrian);
            continue;
        }

        // menu
        int flag = 1;
        while (flag == 1) {
            int pilihan;
            printf("\n\nSilakan pilih menu transaksi:\n");
            printf("1. Setor tunai\n2. Tarik tunai\n3. Transfer\n4. Cek saldo\n5. Selesai transaksi\n");
            printf("Pilihan anda: ");
            scanf("%d", &pilihan);
            switch (pilihan) {
            case 1:
                setor(antrian.data[antrian.front]);
                break;
            case 2:
                tarik(antrian.data[antrian.front]);
                break;
            case 3:
                transfer(antrian.data[antrian.front]);
                break;
            case 4:
                printf("Saldo anda: Rp%.lf", cek_saldo(antrian.data[antrian.front]));
                break;
            case 5:
                flag = 0;
                break;
            default:
                break;
            }
        }
    }

    printf("\nSelesai...");
    return 0;
}

void push(Stack* stack)
{
    int data = 1;
    if (stack->top == LIMIT - 1) {    // jika pointer sudah di paling atas
        printf("Tumpukan sudah penuh\n");
    }
    else {
        stack->top++;  // tambah tumpukan pecahan
        stack->data[stack->top] = data;   // masukkan tumpukan lembaran baru
    }

}
void pop(Stack* stack)
{
    stack->top--; // hapus tumpukan paling atas
}
int size(Stack stack)
{
    return stack.top + 1;    // print jumlah lembar pecahan
}

void insert(Queue* q, User* u) {
    if (q->rear == LIMIT - 1) {         // jika antrian terakhir telah mencapai LIMIT
        printf("Antrian sudah penuh.\n");
    }
    else {
        if (q->front == -1) {       // jika antrian masing kosong
            q->front = 0;           // jadikan antrian yang pertama
        }
        q->rear++;              // tambah jumlah data dalam antrian
        q->data[q->rear] = u;   // insert data ke antrian paling belakang
    }
}
void delete(Queue* q) {
    if (isEmpty(q)) {       // cek apakah sudah kosong
        printf("Antrian sudah kosong.\n");
    }
    else {
        q->front++;     // majukan antrian (yang pertama keluar)
    }
}
int isEmpty(Queue* q) {
    if (q->front == -1 || q->front > q->rear) {     // jika tidak ada data di antrian terdepan
        return 1;
    }
    return 0;
}

int login(User u) {
    int pin, coba = 1;

    while (coba <= 3) {     // kenapa 3? Percobaan memasukkan PIN maksimal 3x
        printf("Nomor rekening: %d\n", u.norek);
        printf("Masukkan PIN Anda:\n");
        printf("PIN: ");
        scanf("%d", &pin);

        if (u.pin == pin) {     // cek keseuaian PIN yang di input
            return 1;
        }

        printf("Gagal. Silakan coba lagi.\n");
        coba++;     // increase jumlah percobaan
    }

    return -1;
}
int search(User cari) {
    for (int i = 0; i < USER_MAX; i++) {        // implementasi searching (linear search)
        if (cari.norek == user[i].norek) {      // cari nomor rekening di dalam array 1 per satu
            return i;       // jika ketemu kembalian nomor index nya
        }
    }

    return -1;      // jika tidak ketemu
}
void view_pecahan() {
    // proses bubble sort
    for (int i = 0; i < JML_PECAHAN - 1; i++) {
        for (int j = 0; j < JML_PECAHAN - i - 1; j++) {
            if (size(pecahan[j]) < size(pecahan[j + 1])) {      // jika nilai jumlah pecahan sebelah kiri lebih kecil, tukar ke sebelah kanan
                Stack temp = pecahan[j];
                pecahan[j] = pecahan[j + 1];
                pecahan[j + 1] = temp;
            }
        }
    }

    // print daftar pecahan setelah di sorting
    printf("Lembar pecahan:\n");
    for (int i = 0; i < JML_PECAHAN; i++) {
        printf("%d. %s - %d lembar\n", (i + 1), pecahan[i].nominalStr, size(pecahan[i]));
    }
}

double cek_saldo(User* asal) {
    return asal->saldo;
}
void transfer(User* asal) {
    User tujuan;
    int norek_tujuan;
    double nominal;

    printf("Nomor rekening tujuan: ");
    scanf("%d", &norek_tujuan);
    tujuan.norek = norek_tujuan;

    int index_tujuan = search(tujuan);      // ambil index nomor rekening tujuan pada array user global

    if (index_tujuan >= 0) {        // lebih dari 0 berarti data rekening ada
        printf("Masukkan nominal: ");
        scanf("%lf", &nominal);

        if (nominal < asal->saldo) {        // cek jika saldo mencukupi
            user[index_tujuan].saldo += nominal;
            asal->saldo -= nominal;
            printf("Transaksi berhasil.\n");
        }
        else
            printf("Saldo tidak cukup");
    }
    else
        printf("Nomor rekening tidak ditemukan.\n");
}
void setor(User* asal) {
    int pilihan, jml_lembar;
    view_pecahan();     // tampilkan daftar pecahan

    printf("Pilih: ");
    scanf("%d", &pilihan);

    printf("Masukkan jumlah lembar kertas: ");
    scanf("%d", &jml_lembar);

    if (pilihan >= 1 && pilihan <= 4) {     // cek apakah pilihan valid (1-4)
        pilihan--;
        if (size(pecahan[pilihan]) + jml_lembar <= LIMIT) {         // cek apakah masih dibawah LIMIT
            for (int i = 0; i < jml_lembar; i++)
                push(&pecahan[pilihan]);

            asal->saldo += pecahan[pilihan].nominal * jml_lembar;
            printf("Transaksi berhasil.\n");
        }
        else {
            printf("Transaksi gagal. Cakupan lembaran mencapai LIMIT\n");       // gagal karena pecahan sudah mencapai LIMIT
        }
    }
    else {
        printf("Pilihan tidak valid.\n");
    }
}
void tarik(User* asal) {
    int pilihan, jml_lembar;
    view_pecahan();

    printf("Pilih: ");
    scanf("%d", &pilihan);

    printf("Masukkan jumlah lembar kertas: ");
    scanf("%d", &jml_lembar);

    double total = 0;

    if (pilihan >= 1 && pilihan <= 4) {     // cek apakah pilihan valid (1-4)
        pilihan--;
        total = pecahan[pilihan].nominal * jml_lembar;
        if (total <= asal->saldo) {         // jika jumlah tarik tunai tidak melebihi saldo di User.
            if (jml_lembar <= size(pecahan[pilihan])) {     // jika jumlah lembar tidak melebihi sisa lembar yang ada.
                asal->saldo -= total;
                for (int i = 0; i < jml_lembar; i++)
                    pop(&pecahan[pilihan]);

                printf("Transaksi berhasil.\n");
            }
            else {
                printf("Transaksi gagal. Lembaran pecahan tidak mencukupi.\n");
            }
        }
        else {
            printf("Transaksi gagal. Saldo tidak mencukupi.\n");
        }
    }
}
