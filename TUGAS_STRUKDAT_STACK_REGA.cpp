#include <stdio.h>
#include <stdlib.h>

#define MAKS_STACK 20

struct node {
    int data;
    struct node *next;
};

typedef struct node node;

void pushStack(node **head, int value);
void popStack(node **head);
void topStack(node *head);
void emptyStack(node *head);
void countStack(node *head);
void destroyStack(node **head);
void printStack(node *head);
void isFullStack(node *head);

int main() {
    node *head = NULL;
    char pilih;
    int value;

    do {
        system("cls");
        printf("MENU PILIHAN OPERASI STACK: \n");
        printf("\n1. push stack\n");
        printf("2. pop stack\n");
        printf("3. stack top\n");
        printf("4. empty stack\n");
        printf("5. stack count\n");
        printf("6. destroy stack\n");
        printf("7. print stack\n");
        printf("8. full stack\n");
        printf("\nMASUKKAN PILIHAN (masukkan q untuk keluar) : ");
        fflush(stdin);
        scanf(" %c", &pilih);

        switch (pilih) {
            case '1':
                printf("Masukkan nilai yang ingin dimasukkan: ");
                scanf("%d", &value);
                pushStack(&head, value);
                break;
            case '2':
                popStack(&head);
                break;
            case '3':
                topStack(head);
                break;
            case '4':
                emptyStack(head);
                break;
            case '5':
                countStack(head);
                break;
            case '6':
                destroyStack(&head);
                break;
            case '7':
                printStack(head);
                break;
            case '8':
                isFullStack(head);
                break;
            case 'q':
                destroyStack(&head);
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
        if (pilih != 'q') {
            printf("Tekan tombol apapun untuk melanjutkan...\n");
            getchar();
            getchar();
        }
    } while (pilih != 'q');

    return 0;
}

void pushStack(node **head, int value) {
    int count = 0;
    node *current = *head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    if (count >= MAKS_STACK) {
        printf("Stack penuh! Tidak dapat menambah isian lagi.\n");
        return;
    }

    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
    printf("Nilai %d telah ditambahkan ke dalam stack.\n", value);
}

void popStack(node **head) {
    if (*head == NULL) {
        printf("Stack kosong! Tidak ada isisan yang bisa dihapus.\n");
    } else {
        node *temp = *head;
        *head = (*head)->next;
        printf("Nilai %d telah dihapus dari stack.\n", temp->data);
        free(temp);
    }
}

void topStack(node *head) {
    if (head == NULL) {
        printf("Stack kosong!\n");
    } else {
        printf("isian teratas stack: %d\n", head->data);
    }
}

void emptyStack(node *head) {
    if (head == NULL) {
        printf("Stack kosong.\n");
    } else {
        printf("Stack tidak kosong.\n");
    }
}

void countStack(node *head) {
    int count = 0;
    node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Jumlah isian dalam stack: %d\n", count);
}

void destroyStack(node **head) {
    node *current = *head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    printf("Stack telah dihancurkan.\n");
}

void printStack(node *head) {
    if (head == NULL) {
        printf("Stack kosong!\n");
    } else {
        node *current = head;
        printf("Isi stack: ");
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

void isFullStack(node *head) {
    int count = 0;
    node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    if (count >= MAKS_STACK) {
        printf("Stack penuh.\n");
    } else {
        printf("Stack belum penuh.\n");
    }
}

