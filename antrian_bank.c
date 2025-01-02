#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 100 // Kapasitas maksimal antrian

typedef struct {
    int id_nasabah;
    char nama_nasabah[50];
    int nomor_antrian;
    char jenis_layanan[20];
    char waktu_kedatangan[20];
    char status[20];
} Nasabah;

typedef struct {
    Nasabah queue[MAX_QUEUE];
    int front;
    int rear;
} Queue;

// Inisialisasi antrian
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Mengecek apakah antrian kosong
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Mengecek apakah antrian penuh
int isFull(Queue *q) {
    return q->rear == MAX_QUEUE - 1;
}

// Memeriksa apakah ID nasabah sudah ada di antrian
int isIdExists(Queue *q, int id) {
    for (int i = q->front; i <= q->rear; i++) {
        if (q->queue[i].id_nasabah == id) {
            return 1; // ID sudah ada
        }
    }
    return 0; // ID tidak ditemukan
}

// Menambahkan nasabah ke antrian
void addQueue(Queue *q, Nasabah n) {
    if (isFull(q)) {
        printf("Antrian penuh! Tidak dapat menambahkan nasabah.\n");
        return;
    }

    // Cek apakah ID nasabah sudah ada
    if (isIdExists(q, n.id_nasabah)) {
        printf("Nasabah dengan ID %d sudah ada dalam antrian!\n", n.id_nasabah);
        return;
    }

    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->queue[q->rear] = n;
    printf("Nasabah dengan nomor antrian %d ditambahkan ke antrian.\n", n.nomor_antrian);
}

// Menghapus nasabah dari antrian jika status selesai
void delQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong! Tidak ada nasabah untuk dihapus.\n");
        return;
    }
    Nasabah n = q->queue[q->front];
    printf("Nasabah dengan nomor antrian %d sedang dilayani dan dihapus dari antrian.\n", n.nomor_antrian);
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
}

// Melihat data nasabah di depan antrian
void peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong! Tidak ada nasabah di depan.\n");
        return;
    }
    Nasabah n = q->queue[q->front];
    printf("Nasabah di depan antrian:\n");
    printf("Nomor Antrian: %d, Nama: %s, Jenis Layanan: %s, Status: %s\n",
           n.nomor_antrian, n.nama_nasabah, n.jenis_layanan, n.status);
}

// Melihat semua nasabah berdasarkan jenis layanan
void peekAll(Queue *q, char *jenis_layanan) {
    if (isEmpty(q)) {
        printf("Antrian kosong! Tidak ada nasabah.\n");
        return;
    }
    printf("Daftar nasabah dengan jenis layanan '%s':\n", jenis_layanan);
    for (int i = q->front; i <= q->rear; i++) {
        if (strcmp(q->queue[i].jenis_layanan, jenis_layanan) == 0) {
            printf("Nomor Antrian: %d, Nama: %s, Status: %s\n",
                   q->queue[i].nomor_antrian,
                   q->queue[i].nama_nasabah,
                   q->queue[i].status);
        }
    }
}

// Fungsi untuk menampilkan menu
void showMenu() {
    printf("\n=== Sistem Antrian Bank ===\n");
    printf("1. Tambahkan Nasabah\n");
    printf("2. Layani Nasabah (Hapus dari Antrian)\n");
    printf("3. Lihat Nasabah di Depan Antrian\n");
    printf("4. Lihat Semua Nasabah Berdasarkan Jenis Layanan\n");
    printf("5. Cek Apakah Antrian Kosong\n");
    printf("6. Cek Apakah Antrian Penuh\n");
    printf("7. Keluar\n");
    printf("Pilih menu: ");
}

// Fungsi utama
int main() {
    Queue antrian;
    initializeQueue(&antrian);

    int pilihan;
    do {
        showMenu();
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer newline

        switch (pilihan) {
        case 1: {
            // Tambahkan Nasabah
            Nasabah n;
            printf("Masukkan ID Nasabah: ");
            scanf("%d", &n.id_nasabah);
            getchar();
            printf("Masukkan Nama Nasabah: ");
            fgets(n.nama_nasabah, sizeof(n.nama_nasabah), stdin);
            n.nama_nasabah[strcspn(n.nama_nasabah, "\n")] = 0; // Hapus newline
            printf("Masukkan Nomor Antrian: ");
            scanf("%d", &n.nomor_antrian);
            getchar();
            printf("Masukkan Jenis Layanan (teller/customer service): ");
            fgets(n.jenis_layanan, sizeof(n.jenis_layanan), stdin);
            n.jenis_layanan[strcspn(n.jenis_layanan, "\n")] = 0;
            printf("Masukkan Waktu Kedatangan: ");
            fgets(n.waktu_kedatangan, sizeof(n.waktu_kedatangan), stdin);
            n.waktu_kedatangan[strcspn(n.waktu_kedatangan, "\n")] = 0;
            strcpy(n.status, "menunggu");
            addQueue(&antrian, n);
            break;
        }
        case 2:
            // Layani Nasabah
            delQueue(&antrian);
            break;

        case 3:
            // Lihat Nasabah di Depan
            peek(&antrian);
            break;

        case 4: {
            // Lihat Semua Nasabah Berdasarkan Jenis Layanan
            char jenis_layanan[20];
            printf("Masukkan Jenis Layanan (teller/customer service): ");
            fgets(jenis_layanan, sizeof(jenis_layanan), stdin);
            jenis_layanan[strcspn(jenis_layanan, "\n")] = 0;
            peekAll(&antrian, jenis_layanan);
            break;
        }
        case 5:
            // Cek apakah antrian kosong
            if (isEmpty(&antrian)) {
                printf("Antrian kosong.\n");
            } else {
                printf("Antrian tidak kosong.\n");
            }
            break;

        case 6:
            // Cek apakah antrian penuh
            if (isFull(&antrian)) {
                printf("Antrian penuh.\n");
            } else {
                printf("Antrian belum penuh.\n");
            }
            break;

        case 7:
            printf("Keluar dari sistem. Terima kasih!\n");
            break;

        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 7);

    return 0;
}
