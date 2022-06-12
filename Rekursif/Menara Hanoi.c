// Kelompok 2 (Genap) Kelas D

#include <stdio.h>

void hanoi(int n, char a, char b, char c) {
    if (n == 1) {
        printf("%c pindah ke %c\n", a, c);
    } else {
        hanoi(n-1, a, c, b);
        hanoi(1, a, b, c);
        hanoi(n-1, b, a, c);
    }
}

int main() {
    int piring;
    printf("Masukkan Jumlah Piringan: ");
    scanf("%d", &piring);

    hanoi(piring, 'A', 'B', 'C');
}
