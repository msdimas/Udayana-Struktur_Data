#include <stdio.h>
#include <stdlib.h>


struct data
{
    int key; int IP;
};

struct data *array; int kapasitas = 10; int size = 0;
char* nama[10]={"Gary Melvin Lie", "SAIFULLOH RAHMAN", "DIMAS FIRMANSYAH", "I Komang Gede Apriana", 
"Anugrah Ignatius Sitinjak", "Albert Okario", "I PUTU TEDDY DHARMA WIJAYA", 
"Anak Agung Ngurah Frady Cakra negara", "I GUSTI PUTU WISNU WARDHANA", "I Made Sudarsana Taksa Wibawa"};
char* tempat[10]={"Kelas AS", "Kelas BD", "Kelas CM", "Kelas DG", "Kelas EQ", "Gedung Informatika", 
"Gedung Matematika", "Gedung Fisika", "Gedung Kimia", "Gedung Biologi"};


int fungsiHash(int key)
{
    return (key % kapasitas);
}


void init_array()
{
array = (struct data *)malloc(kapasitas * sizeof(struct data)); for (int i = 0; i < kapasitas; i++)
{
array[i].key = 0;
array[i].IP = 0;
}
}


void insert(int key, int IP)
{
    int index = fungsiHash(key);

        if (array[index].IP == 0)
        {
        array[index].key = key; array[index].IP = IP; size++;
        printf("\n Key (%d) Sudah Dimasukan \n", key);
        }

else if (array[index].key == key)
{
array[index].IP = IP;
}
}


void remove_data(int key)
{
    int index = fungsiHash(key);
    if (array[index].IP == 0)
    {
    printf("\n Key ini tidak ada \n");
    }
else
{
array[index].key = 0;
array[index].IP = 0; size--;
printf("\n Key (%d) sudah di hapus\n", key);
}
}


void display()
{
    int i;
    for (i = 0; i < kapasitas; i++)
{
if (array[i].IP == 0)
{

printf("\nIndex ke-[%d]: \n", i);
}
else
{
int p = rand()%10;
printf("Key: %d | IP : %d | Nama User : %s | Letak Komputer : %s\n",
array[i].key, array[i].IP, nama[p], tempat[p]);
}
}
}


int main()
{
    int pilihan, key, IP, n; int c = 0;
    int p = rand()%10;
    init_array();

do
{
system("cls");
printf("================================================================================\n");
printf("====================  Program Proses Mapping Metode Hash IP	================\n");
printf("================================================================================\n\n");
printf("1. Tambahkan Data User ke Hash Table\n");
printf("2. Hapus Data User dari Hash Table\n");
printf("3. Tampilkan Data User Hash Table\n");
printf("4. Exit dari Main Menu\n");
printf("\n Masukkan Pilihan Anda : ");
scanf("%d", &pilihan);
switch (pilihan)
{
case 1:
printf("Masukan Key : "); scanf("%d", &key);
printf("Masukan IP (Tanpa Titik) : ");
scanf("%d", &IP); insert(key, IP);
break;

case 2:
printf("Masukkan key untuk dihapus :"); 
scanf("%d", &key);
remove_data(key);
break;

case 3: display();
break;

case 4:
printf ("Terimakasih Sudah Menggunakan Program");
break;

default:
printf("INPUT SALAH!!\n");
}

printf("\nTekan Enter untuk kembali ke menu\n");
}
while (pilihan != 4);
return 0;
}
