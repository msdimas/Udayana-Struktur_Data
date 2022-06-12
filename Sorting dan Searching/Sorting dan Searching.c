#include <stdio.h>
#include <stdlib.h>

struct a{
    int n;
    struct a *next;
}*h;

struct a *linkAddress(struct a *help, int no) {
    for(int i = 0; i < no; i++) {
        help = help -> next;
    }
    return help;
};

void viewData(struct a *view) {
    printf("Data dalam linked list : ");
    while(view) {
        printf("%d\t", view -> n);
        view = view -> next;
    }
    printf("\n");
}

int returnStruct(struct a *help) {
    int jum=0;
    while(help) {
        jum++;
        help = help -> next;
    }
    return jum;
}

void dataInsert(int data, struct a *helpA) {
    struct a *help;
    if(helpA -> n > data) {
        help = (struct a*)malloc(sizeof(struct a));
        help -> n = data;
        help -> next = helpA;
        h = help;
    } else {
        while(helpA -> next != NULL) {
            if(helpA -> n < data){
                if(helpA -> next -> n > data) {
                    help = helpA -> next;
                    helpA -> next = (struct a*)malloc(sizeof(struct a));
                    helpA -> next -> n = data;
                    helpA -> next -> next = help;
                }
            }
            helpA = helpA -> next;
        }
    }
}

int binarySearch(int data, struct a *helpB) {
    struct a *help;
    int l=0;
    int r=returnStruct(helpB);
    int ketemu=0;
    int m=(l+r)/2;
    while(l<=r && !ketemu) {
        m=(l+r)/2;
        help=linkAddress(helpB,m);
        if(data>help->n) {
            l=m+1;
        }
        if(data==help->n) {
            ketemu=1;
            return 1;
        }
        if(data<help->n){
            r=m-1;
        }
    }
    dataInsert(data,helpB);
return 0;
}

void viewDataArray(int myArray[], int jumlahkuy) {
    printf("Data dalam array : ");
    for(int z=0; z<jumlahkuy; z++) {
        printf("%d\t", myArray[z]);
    }
    printf("\n");
}

void insArr(int data, int indeks, int arr[], int *jumlahkuy) {
    int i;
    int temp;
    if(data<arr[indeks]) {
        i=indeks;
    }
    if(data>arr[indeks]) {
        i=indeks+1;
    }
    int temp1=arr[i];
    arr[i]=data;
    while(arr[i]) {
        temp=arr[i+1];
        arr[i+1]=temp1;
        temp1=temp;
        i++;
    }
(*jumlahkuy)++;
}

int searchMyArray(int arraylah[], int datakuy, int *jumlahkuy) {
    int l=0;
    int r=*jumlahkuy-1;
    int ketemu=0;
    int m;
    while((l<=r)&&(!ketemu)) {
        m=(l+r)/2;
        if(datakuy>arraylah[m])
    l=m+1;
    if(datakuy==arraylah[m])
    ketemu=1;
    if(datakuy<arraylah[m])
        r=m-1;
    }
    if(ketemu==0){
        insArr(datakuy,m,arraylah,jumlahkuy);
    }
return ketemu;
}

int main(){

    printf("\nSINGLE LINKED LIST\n");
    struct a *satu=(struct a*)malloc(sizeof(struct a)); satu->n=10;
    struct a *dua=(struct a*)malloc(sizeof(struct a)); dua->n=33;
    struct a *tiga=(struct a*)malloc(sizeof(struct a)); tiga->n=46;
    struct a *empat=(struct a*)malloc(sizeof(struct a)); empat->n=65;
    struct a *lima=(struct a*)malloc(sizeof(struct a)); lima->n=119;
    h=satu;
    h->next=dua;
    h->next->next=tiga;
    h->next->next->next=empat;
    h->next->next->next->next=lima;
    h->next->next->next->next->next=NULL;
    //pendefinisian single linked list
    viewData(h);

    printf("Data 1 : %d\n", binarySearch(1,h));
    printf("Data 2 : %d\n", binarySearch(2,h));
    printf("Data 6 : %d\n", binarySearch(6,h));
    printf("Data 7 : %d\n", binarySearch(7,h));
    printf("Data 8 : %d\n", binarySearch(10,h));
    viewData(h);

    printf("\nARRAY\n");
    int myArray[100];
    myArray[0]=2; myArray[1]=3; myArray[2]=5; myArray[3]=7; myArray[4]=11;
    int nmyArray=5;
    viewDataArray(myArray,nmyArray);
    printf("Data 1 : %d\n", searchMyArray(myArray,1,&nmyArray));
    printf("Data 2 : %d\n", searchMyArray(myArray,2,&nmyArray));
    printf("Data 6 : %d\n", searchMyArray(myArray,6,&nmyArray));
    printf("Data 7 : %d\n", searchMyArray(myArray,7,&nmyArray));
    printf("Data 8 : %d\n", searchMyArray(myArray,8,&nmyArray));
    viewDataArray(myArray,nmyArray);
}
