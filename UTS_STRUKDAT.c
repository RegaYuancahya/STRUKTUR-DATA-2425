#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANAK 20

struct node {
    char name[50];
    char gender[10];
    struct node *next;
    struct node *prev;
};
typedef struct node node;

void tambahAnak(node **head, int *size);
void tampilSemua(node *head);
void tampilPerGender(node *head, char gender[]);
void hapusAnak(node **head, int *size);
void tambahAnakKembar(node **head, int *size);
int genderSama(node *cur);
void aturanGender(node **head, node *newNode);


int main() {
    node *head = NULL;
    int size = 0;
    char pilih;

    do {
        printf("\nMasukkan pilihan:\n");
        printf("1. Tambah mahasiswa\n");
        printf("2. Tambah anak kembar\n");
        printf("3. Tampilkan semua lingkaran mahasiswa\n");
        printf("4. Tampilkan lingkaran mahasiswa\n");
        printf("5. Tampilkan lingkaran mahasiswi\n");
        printf("6. Mengeluarkan mahasiswa dari lingkaran\n");
        printf("q. Keluar\n");
        printf("MASUKKAN PILIHAN: ");
        fflush(stdin);
        scanf(" %c", &pilih);
        if (pilih == '1')
            tambahAnak(&head, &size);
        else if (pilih == '2')
            tambahAnakKembar(&head, &size);
        else if (pilih == '3')
            tampilSemua(head);
        else if (pilih == '4')
            tampilPerGender(head, "laki-laki");
        else if (pilih == '5')
            tampilPerGender(head, "perempuan");
        else if (pilih == '6')
            hapusAnak(&head, &size);
    } while (pilih != 'q');

    return 0;
}


void tambahAnak(node **head, int *size) {
    if (*size >= MAX_ANAK) {
        printf("Lingkaran sudah penuh, maksimal 20 mahasiswa!\n");
        return;
    }

    char name[50], gender[10];
    node *newNode, *cur;

    printf("Masukkan nama mahasiswa: ");
    scanf("%s", name);
    printf("Masukkan jenis kelamin (laki-laki/perempuan): ");
    scanf("%s", gender);

    newNode = (node *)malloc(sizeof(node));
    strcpy(newNode->name, name);
    strcpy(newNode->gender, gender);

    if (*head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
    } else {
        aturanGender(head, newNode);
    }

    (*size)++;
}


void aturanGender(node **head, node *newNode) {
    node *cur = *head;
    int pilihan;

    printf("Apakah mahasiswa ini ingin bersebelahan dengan sesama jenis kelamin?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {

        do {
            if (strcmp(cur->gender, newNode->gender) == 0) {
                break;
            }
            cur = cur->next;
        } while (cur != *head);
    } else {

        do {
            if (genderSama(cur)) {
                break;
            }
            cur = cur->next;
        } while (cur != *head);
    }

    newNode->next = cur->next;
    newNode->prev = cur;
    cur->next->prev = newNode;
    cur->next = newNode;
}



int genderSama(node *cur) {
    return strcmp(cur->next->gender, cur->gender) == 0;
}


void tambahAnakKembar(node **head, int *size) {
    if (*size + 2 > MAX_ANAK) {
        printf("Tidak dapat menambahkan anak kembar, lingkaran hampir penuh!\n");
        return;
    }

    char name1[50], name2[50], gender[10];
    node *newNode1, *newNode2;

    printf("Masukkan nama anak pertama: ");
    scanf("%s", name1);
    printf("Masukkan nama anak kedua: ");
    scanf("%s", name2);
    printf("Masukkan jenis kelamin (laki-laki/perempuan): ");
    scanf("%s", gender);

    newNode1 = (node *)malloc(sizeof(node));
    newNode2 = (node *)malloc(sizeof(node));
    strcpy(newNode1->name, name1);
    strcpy(newNode2->name, name2);
    strcpy(newNode1->gender, gender);
    strcpy(newNode2->gender, gender);

    if (*head == NULL) {
        newNode1->next = newNode2;
        newNode1->prev = newNode2;
        newNode2->next = newNode1;
        newNode2->prev = newNode1;
        *head = newNode1;
    } else {
        aturanGender(head, newNode1);
        newNode2->next = newNode1->next;
        newNode2->prev = newNode1;
        newNode1->next->prev = newNode2;
        newNode1->next = newNode2;
    }

    *size += 2;
}


void tampilSemua(node *head) {
    if (head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }

    node *cur = head;
    do {
        printf("%s (%s) <-> ", cur->name, cur->gender);
        cur = cur->next;
    } while (cur != head);

    printf("%s (%s)\n", head->name, head->gender);
}


void tampilPerGender(node *head, char gender[]) {
    if (head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }

    node *cur = head;
    int found = 0;
    do {
        if (strcmp(cur->gender, gender) == 0) {
            printf("%s (%s) <-> ", cur->name, cur->gender);
            found = 1;
        }
        cur = cur->next;
    } while (cur != head);

    if (!found) {
        printf("Tidak ada mahasiswa dengan jenis kelamin %s\n", gender);
    } else {

        node *first = head;
        while (strcmp(first->gender, gender) != 0) {
            first = first->next;
        }
        printf("%s (%s)\n", first->name, first->gender);
    }
}


void hapusAnak(node **head, int *size) {
    if (*head == NULL) {
        printf("Lingkaran kosong!\n");
        return;
    }

    char name[50];
    node *cur = *head, *temp;

    printf("Masukkan nama mahasiswa yang ingin keluar: ");
    scanf("%s", name);

    do {
        if (strcmp(cur->name, name) == 0) {
            if (cur->next == cur) {
                free(cur);
                *head = NULL;
            } else {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                if (*head == cur) {
                    *head = cur->next;
                }
                free(cur);
            }
            (*size)--;
            printf("mahasiswa %s telah keluar dari lingkaran.\n", name);
            return;
        }
        cur = cur->next;
    } while (cur != *head);

    printf("mahasiswa dengan nama %s tidak ditemukan!\n", name);
}
