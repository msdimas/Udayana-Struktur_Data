#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 20 //maksimum data queue

//Deklarasi struct antrian
struct Queue {
	int front, rear, data[MAX];
};

struct Queue Q;

int total = 0;


//cek apakah antrian penuh
bool isFull() {
	return Q.rear == MAX;
}

//cek apakah antrian kosong
bool isEmpty() {
	return Q.rear == 0;
}

//Menampilkan Queue
void printQueue() {
	if (isEmpty()) {
    printf("Antrian Kosong\n");
	} else {
        printf("QUEUE : ");
		for (int i = Q.front; i < Q.rear; i++)
            printf("%d %s", Q.data[i], (Q.rear-1 == i) ? "" : ", ");
            printf("\n");
  }
}

//manambahkan data ke antrian
void enqueue() {
	if (isFull()) {
        printf("Antrian Penuh!\n");
	}
	else {
		int data;
        printf("Masukkan Data: ");
        scanf("%d", &data);
		Q.data[Q.rear] = data;
		Q.rear++;
        printf("Data Ditambahkan\n");
		printQueue();
	}
}

// mengambil data dari antrian
void dequeue() {
	if (isEmpty())
	{
        printf("Antrian Masih Kosong\n");
	}
	else{
        printf("Mengambil Data \" %d \" ... \n", Q.data[Q.front]);
		for (int i = Q.front; i < Q.rear; i++)
			Q.data[i] = Q.data[i + 1];
		Q.rear--;
		printQueue();
	}
}

// menampilkan total data
void totalData() {
    for (int i = 0; i < Q.rear; i++) {
        total = total + Q.data[i];
    }
    printf("Total: %d\n", total);
    printf("QUEUE : ");
    for (int i = Q.front; i < Q.rear; i++)
        printf("%d %s", Q.data[i], (Q.rear-1 == i) ? "" : ", ");
        printf("\n");
}

// menampilan rata-rata
void rerata() {
    if (Q.rear == 0) {
        printf("Data Masih Kosong\n");
    } else {
        for (int i = 0; i < Q.rear; i++) {
            total = total + Q.data[i];
        }
        printf("Rata-rata: %d\n", total/Q.rear);
    }
    printf("QUEUE : ");
    for (int i = Q.front; i < Q.rear; i++)
    printf("%d %s", Q.data[i], (Q.rear-1 == i) ? "" : ", ");
    printf("\n");
}

// mencari nilai terbesar
void dataTerbesar() {
    int max_dat = Q.data[0];
    for(int i = 0; i < Q.rear; i++) {
        if(Q.data[i] > max_dat) {
            max_dat = Q.data[i];
        }
    }
    printf("Data Terbesar: %d\n", max_dat);
    printf("QUEUE : ");
    for (int i = Q.front; i < Q.rear; i++)
    printf("%d %s", Q.data[i], (Q.rear-1 == i) ? "" : ", ");
    printf("\n");
}

// mencari nilai terkecil
void dataTerkecil() {
    int min_dat = Q.data[0];
    for(int i = 0; i < Q.rear; i++) {
        if(Q.data[i] < min_dat) {
            min_dat = Q.data[i];
        }
    }
    printf("Data Terkecil: %d\n", min_dat);
    printf("QUEUE : ");
    for (int i = Q.front; i < Q.rear; i++)
    printf("%d %s", Q.data[i], (Q.rear-1 == i) ? "" : ", ");
    printf("\n");
}

int main() {
	int choose;
	do
	{
		//Tampilan menu
        printf("\n\nMenu\n\n");
        printf("1. EnQueue\n");
        printf("2. DeQueue\n");
        printf("3. Total Data\n");
        printf("4. Rata-rata\n");
        printf("5. Data Terbesar\n");
        printf("6. Data Terkecil\n");
        printf("7. Keluar\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &choose);

		switch (choose)
		{
		case 1:
            system("cls");
			enqueue();
			break;
            _sleep(1);
		case 2:
            system("cls");
			dequeue();
			break;
            _sleep(1);
        case 3:
            system("cls");
            totalData();
            break;
            _sleep(1);
        case 4:
            system("cls");
            rerata();
            break;
            _sleep(1);
        case 5:
            system("cls");
            dataTerbesar();
            _sleep(1);
            break;
        case 6:
            system("cls");
            dataTerkecil(); 
            _sleep(1);
            break;
        case 7:
            return 0;
		default:
            printf("Inputan Invalid");
			break;
		}
	} while (choose !=7);
	return 0;
}