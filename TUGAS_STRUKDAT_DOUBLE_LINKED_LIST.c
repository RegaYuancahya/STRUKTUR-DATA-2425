#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *right;
    struct node *left;
};
typedef struct node node;

// Function declarations
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

//========================================================

int main()
{
    node *head;
    char pilih;
    int hasil, jumlah, total;

    head = NULL;
    do
    {
        system("cls"); // Bisa di-comment sementara untuk debugging
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

        if (pilih == '1')
        {
            tambahAwal(&head);
            getchar();
        }
        else if (pilih == '2')
        {
            tambahData(&head);
            getchar();
        }
        else if (pilih == '3')
        {
            tambahakhir(&head);
            getchar();
        }
        else if (pilih == '4')
        {
            hapusawal(&head);
            getchar();
        }
        else if (pilih == '5')
        {
            hapustengah(&head);
            getchar();
        }
        else if (pilih == '6')
        {
            hapusakhir(&head);
            getchar();
        }
        else if (pilih == '7')
        {
            tranverse(head);
            getchar();
        }
        else if (pilih == '8')
        {
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
        }
        else if (pilih == '9')
        {
            system("cls");
            jumlah = jumlahdata(head);
            printf("Jumlah data di dalam list : %d", jumlah);
            getchar();
        }
        else if (pilih == '0')
        {
            system("cls");
            total = totaldata(head);
            printf("total seluruh data di list : %d", total);
            getchar();
        }
    } while (pilih != 'q');

    return 0;
}

void tambahAwal(node **head)
{
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL)
    {
        pNew->data = bil;
        pNew->right = *head;
        pNew->left = NULL;

        if (*head != NULL)
        {
            (*head)->left = pNew;
        }
        *head = pNew;
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
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos)
    {
        pCur = pCur->right;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL)
    {
        printf("\nnode tidak ditemukan");
        getch();
    }
    else if (pNew == NULL)
    {
        printf("\nalokasi memori gagal");
        getch();
    }
    else
    {
        pNew->data = bil;
        pNew->right = pCur->right;
        pNew->left = pCur;

        if (pCur->right != NULL)
        {
            pCur->right->left = pNew;
        }
        pCur->right = pNew;
    }
}

//========================================================

void tambahakhir(node **head)
{
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew == NULL)
    {
        printf("\nalokasi memori gagal");
        getch();
        return;
    }

    pNew->data = bil;
    pNew->right = NULL;
    pNew->left = NULL;

    if (*head == NULL)
    {
        *head = pNew;
    }
    else
    {
        pCur = *head;
        while (pCur->right != NULL)
        {
            pCur = pCur->right;
        }
        pCur->right = pNew;
        pNew->left = pCur;
    }
}

//========================================================

void hapusawal(node **head)
{
    node *pTempt;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    pTempt = *head;
    *head = (*head)->right;
    if (*head != NULL)
    {
        (*head)->left = NULL;
    }
    free(pTempt);
    printf("Data di awal list sudah terhapus\n");
}

//========================================================

void hapustengah(node **head)
{
    int bil;
    node *pCur;

    system("cls");
    tranverse(*head);
    printf("\nmasukkan data yang akan dihapus : ");
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != bil)
    {
        pCur = pCur->right;
    }

    if (pCur == NULL)
    {
        printf("\ndata tidak ditemukan");
        getch();
    }
    else
    {
        if (pCur->left != NULL)
        {
            pCur->left->right = pCur->right;
        }
        if (pCur->right != NULL)
        {
            pCur->right->left = pCur->left;
        }
        if (pCur == *head)
        {
            *head = pCur->right;
        }
        free(pCur);
        printf("\ndata sudah terhapus");
        getch();
    }
}

//========================================================

void hapusakhir(node **head)
{
    node *pCur;

    system("cls");
    if (*head == NULL)
    {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    pCur = *head;
    while (pCur->right != NULL)
    {
        pCur = pCur->right;
    }

    if (pCur->left != NULL)
    {
        pCur->left->right = NULL;
    }
    else
    {
        *head = NULL;
    }
    free(pCur);
    printf("Node terakhir sudah terhapus.\n");
}

//========================================================

void tranverse(node *head)
{
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL)
    {
        printf("%d", pWalker->data);
        if (pWalker->right != NULL)
        {
            printf(" <-> ");
        }
        pWalker = pWalker->right;
    }
    printf(" <-> NULL\n");
}

//========================================================

int caridata(node *head)
{
    int bil;
    node *pCur = head;
    int pos = 1;

    system("cls");
    printf("Masukkan nilai yang dicari : ");
    scanf("%d", &bil);

    while (pCur != NULL)
    {
        if (pCur->data == bil)
        {
            return pos;
        }
        pCur = pCur->right;
        pos++;
    }
    return -1;
}

//========================================================

int jumlahdata(node *head)
{
    node *pCur = head;
    int count = 0;

    system("cls");
    while (pCur != NULL)
    {
        count++;
        pCur = pCur->right;
    }
    return count;
}

//========================================================

int totaldata(node *head)
{
    node *pCur = head;
    int total = 0;

    while (pCur != NULL)
    {
        total += pCur->data;
        pCur = pCur->right;
    }
    return total;
}
