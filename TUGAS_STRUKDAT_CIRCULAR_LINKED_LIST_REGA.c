#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahData(node **head);
void tambahakhir(node **head);
void hapusawal(node **head);
void hapustengah(node **head);
void hapusakhir(node **head);
void tranverse(node *head);
int caridata(node *head);
int jumlahdata(node *head);
int totaldata(node *head);

int main()
{
    node *head = NULL;
    char pilih;
    int hasil, jumlah, total;

    do
    {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data di awal list\n");
        printf("2. tambah data di tengah list\n");
        printf("3. tambah data di akhir list\n");
        printf("4. hapus data di awal list\n");
        printf("5. hapus data di tengah list\n");
        printf("6. hapus data di akhir list\n");
        printf("7. cetak isi list\n");
        printf("8. cari data di list\n");
        printf("9. jumlah data di list\n");
        printf("0. total seluruh data di list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);
        fflush(stdin);

        switch (pilih)
        {
        case '1':
            tambahAwal(&head);
            getchar();
            break;
        case '2':
            tambahData(&head);
            getchar();
            break;
        case '3':
            tambahakhir(&head);
            getchar();
            break;
        case '4':
            hapusawal(&head);
            getchar();
            break;
        case '5':
            hapustengah(&head);
            getchar();
            break;
        case '6':
            hapusakhir(&head);
            getchar();
            break;
        case '7':
            tranverse(head);
            getchar();
            break;
        case '8':
            hasil = caridata(head);
            if (hasil != -1)
            {
                printf("\nData ditemukan di posisi: %d", hasil);
            }
            else
            {
                printf("\nData tidak ditemukan dalam linked list.");
            }
            getchar();
            getchar();
            break;
        case '9':
            jumlah = jumlahdata(head);
            printf("Jumlah data di dalam list : %d", jumlah);
            getchar();
            break;
        case '0':
            total = totaldata(head);
            printf("Total seluruh data di list : %d", total);
            getchar();
            break;
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head)
{
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL)
    {
        pNew->data = bil;
        if (*head == NULL) // List is empty
        {
            *head = pNew;
            pNew->next = pNew; // Points to itself
        }
        else
        {
            pCur = *head;
            while (pCur->next != *head) // Traverse to the last node
                pCur = pCur->next;

            pNew->next = *head;
            pCur->next = pNew;
            *head = pNew; // Update head to new node
        }
    }
    else
    {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head)
{
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    scanf("%d", &pos);
    printf("\nbilangan : ");
    scanf("%d", &bil);

    pCur = *head;
    do
    {
        if (pCur->data == pos)
            break;
        pCur = pCur->next;
    } while (pCur != *head); // Ensure circular traversal

    if (pCur == *head && pCur->data != pos)
    {
        printf("\nnode tidak ditemukan");
        getch();
    }
    else
    {
        pNew = (node *)malloc(sizeof(node));
        if (pNew == NULL)
        {
            printf("\nalokasi memori gagal");
            getch();
        }
        else
        {
            pNew->data = bil;
            pNew->next = pCur->next;
            pCur->next = pNew;
        }
    }
}

//========================================================

void tambahakhir(node **head)
{
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("masukkan bilangan : ");
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew == NULL)
    {
        printf("\nalokasi memori gagal");
        getch();
        return;
    }

    pNew->data = bil;
    if (*head == NULL) // List is empty
    {
        *head = pNew;
        pNew->next = pNew; // Circular pointer
    }
    else
    {
        pCur = *head;
        while (pCur->next != *head) // Traverse to the last node
            pCur = pCur->next;

        pCur->next = pNew;
        pNew->next = *head; // Ensure circularity
    }
}

//========================================================

void hapusawal(node **head)
{
    node *pCur;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    pCur = *head;
    if (pCur->next == *head) // Single node case
    {
        free(pCur);
        *head = NULL;
    }
    else
    {
        while (pCur->next != *head) // Traverse to the last node
            pCur = pCur->next;

        node *temp = *head;
        pCur->next = (*head)->next;
        *head = (*head)->next;
        free(temp);
    }
    printf("Data di awal list sudah terhapus\n");
}

//========================================================

void hapustengah(node **head)
{
    int bil;
    node *pPrev, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nmasukkan data yang akan dihapus : ");
    scanf("%d", &bil);

    if (*head == NULL)
    {
        printf("List kosong\n");
        return;
    }

    pCur = *head;
    do
    {
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head && pCur->data != bil);

    if (pCur == *head && pCur->data != bil)
    {
        printf("Data tidak ditemukan\n");
    }
    else
    {
        pPrev->next = pCur->next;
        free(pCur);
        printf("Data sudah terhapus\n");
    }
}

//========================================================

void hapusakhir(node **head)
{
    node *pCur, *pPrev;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    pCur = *head;
    if (pCur->next == *head) // Single node case
    {
        free(pCur);
        *head = NULL;
    }
    else
    {
        while (pCur->next != *head)
        {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head;
        free(pCur);
    }
    printf("Node terakhir sudah terhapus.\n");
}

//========================================================

void tranverse(node *head)
{
    node *pWalker;

    system("cls");
    if (head == NULL)
    {
        printf("List kosong\n");
        return;
    }

    pWalker = head;
    do
    {
        printf("%d", pWalker->data);
        pWalker = pWalker->next;
        if (pWalker != head)
            printf(" -> ");
    } while (pWalker != head);

    printf(" -> [head]\n");
}

//========================================================

int caridata(node *head)
{
    int bil, pos = 1;
    node *pCur = head;

    system("cls");
    printf("Masukkan nilai yang dicari : ");
    scanf("%d", &bil);

    if (head == NULL)
        return -1;

    do
    {
        if (pCur->data == bil)
            return pos;
        pCur = pCur->next;
        pos++;
    } while (pCur != head);

    return -1;
}

//========================================================

int jumlahdata(node *head)
{
    int count = 0;
    node *pCur = head;

    if (head == NULL)
        return count;

    do
    {
        count++;
        pCur = pCur->next;
    } while (pCur != head);

    return count;
}

//========================================================

int totaldata(node *head)
{
    int total = 0;
    node *pCur = head;

    if (head == NULL)
        return total;

    do
    {
        total += pCur->data;
        pCur = pCur->next;
    } while (pCur != head);

    return total;
}
