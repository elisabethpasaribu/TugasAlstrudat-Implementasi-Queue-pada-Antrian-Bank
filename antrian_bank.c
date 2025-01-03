#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

struct queue {
    int id_nasabah;
    char nama_nasabah[25];
    int nomor_antrian;
    char jenis_layanan[25];
    char waktu_kedatangan[10];
    char status[15];
};

struct queue tellerQueue[MAX];
struct queue csQueue[MAX];
int headTeller = -1, tailTeller = -1;
int headCS = -1, tailCS = -1;

// Menyimpan nomor antrian terakhir untuk masing-masing jenis layanan
int nomorAntrianLayanan[2] = {0, 0}; 

int isEmpty(int queueType);
int isFull(int queueType);
void Enqueue();
void Dequeue();
void Clear();
void PeekAll();
void checkQueueStatus();
int getNomorAntrian(const char* jenis_layanan);
int menu();
void displayAllCustomers();

int main() {
    int input;
    while (1) {
        input = menu();
        switch (input) {
            case 1:
                Enqueue();
                break;
            case 2:
                Dequeue();
                break;
            case 3:
                Clear();
                break;
            case 4:
                checkQueueStatus();
                break;
            case 5:
                displayAllCustomers();
                break;
            case 6:
                printf("Terima kasih telah menggunakan program ini.\n");
                exit(0);
            default:
                printf("\nPilihan Menu Tidak Tersedia. Silakan Coba Lagi!\n\n");
        }
        printf("\n");
        system("pause");
        system("cls");
    }
    return 0;
}

int isEmpty(int queueType) {
    if (queueType == 1) {
        return headTeller == -1;
    } else if (queueType == 2) {
        return headCS == -1;
    }
    return 1;
}

int isFull(int queueType) {
    if (queueType == 1) {
        return tailTeller == MAX - 1;
    } else if (queueType == 2) {
        return tailCS == MAX - 1;
    }
    return 0;
}

int getNomorAntrian(const char* jenis_layanan) {
    if (strcmp(jenis_layanan, "teller") == 0) {
        return ++nomorAntrianLayanan[0];
    } else if (strcmp(jenis_layanan, "customer service") == 0) {
        return ++nomorAntrianLayanan[1];
    }
    return 0;
}

void Enqueue() {
    struct queue nasabahBaru;

    printf("\nMasukkan ID Nasabah: ");
    scanf("%d", &nasabahBaru.id_nasabah);

    printf("Masukkan Nama Nasabah: ");
    getchar(); // Bersihkan buffer
    fgets(nasabahBaru.nama_nasabah, sizeof(nasabahBaru.nama_nasabah), stdin);
    nasabahBaru.nama_nasabah[strcspn(nasabahBaru.nama_nasabah, "\n")] = '\0';

    printf("Masukkan Jenis Layanan (teller / customer service): ");
    fgets(nasabahBaru.jenis_layanan, sizeof(nasabahBaru.jenis_layanan), stdin);
    nasabahBaru.jenis_layanan[strcspn(nasabahBaru.jenis_layanan, "\n")] = '\0';

    printf("Masukkan Waktu Kedatangan (Jam:Menit): ");
    fgets(nasabahBaru.waktu_kedatangan, sizeof(nasabahBaru.waktu_kedatangan), stdin);
    nasabahBaru.waktu_kedatangan[strcspn(nasabahBaru.waktu_kedatangan, "\n")] = '\0';

    strcpy(nasabahBaru.status, "Menunggu");

    if (strcmp(nasabahBaru.jenis_layanan, "teller") == 0) {
        if (!isFull(1)) {
            if (headTeller == -1) headTeller = 0;
            tailTeller++;
            nasabahBaru.nomor_antrian = getNomorAntrian("teller");
            tellerQueue[tailTeller] = nasabahBaru;
            printf("\nNasabah berhasil ditambahkan ke antrian Teller.\n");
        } else {
            printf("\nAntrian Teller penuh!\n");
        }
    } else if (strcmp(nasabahBaru.jenis_layanan, "customer service") == 0) {
        if (!isFull(2)) {
            if (headCS == -1) headCS = 0;
            tailCS++;
            nasabahBaru.nomor_antrian = getNomorAntrian("customer service");
            csQueue[tailCS] = nasabahBaru;
            printf("\nNasabah berhasil ditambahkan ke antrian Customer Service.\n");
        } else {
            printf("\nAntrian Customer Service penuh!\n");
        }
    } else {
        printf("\nJenis layanan tidak valid!\n");
    }
}

void Dequeue() {
    int pilihan;
    printf("\nPilih Jenis Layanan untuk Dequeue (1: Teller, 2: Customer Service): ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        if (!isEmpty(1)) {
            printf("\nNasabah %s (ID: %d) dari antrian Teller sudah selesai.\n",
                   tellerQueue[headTeller].nama_nasabah, tellerQueue[headTeller].id_nasabah);
            strcpy(tellerQueue[headTeller].status, "Dilayani");
            headTeller++;
            if (headTeller > tailTeller) headTeller = tailTeller = -1;
        } else {
            printf("\nAntrian Teller kosong!\n");
        }
    } else if (pilihan == 2) {
        if (!isEmpty(2)) {
            printf("\nNasabah %s (ID: %d) dari antrian Customer Service sudah selesai.\n",
                   csQueue[headCS].nama_nasabah, csQueue[headCS].id_nasabah);
            strcpy(csQueue[headCS].status, "Dilayani");
            headCS++;
            if (headCS > tailCS) headCS = tailCS = -1;
        } else {
            printf("\nAntrian Customer Service kosong!\n");
        }
    } else {
        printf("\nPilihan tidak valid!\n");
    }
}

void PeekAll() {
    printf("\nDaftar Antrian Teller:\n");
    if (!isEmpty(1)) {
        for (int i = headTeller; i <= tailTeller; i++) {
            if (i == headTeller) strcpy(tellerQueue[i].status, "Sedang Diproses");
            printf("\nNomor Antrian: %d", tellerQueue[i].nomor_antrian);
            printf("\nID Nasabah: %d", tellerQueue[i].id_nasabah);
            printf("\nNama Nasabah: %s", tellerQueue[i].nama_nasabah);
            printf("\nJenis Layanan: %s", tellerQueue[i].jenis_layanan);
            printf("\nWaktu Kedatangan: %s", tellerQueue[i].waktu_kedatangan);
            printf("\nStatus: %s", tellerQueue[i].status);
            printf("\n------------------------");
        }
    } else {
        printf("\nAntrian Teller kosong!");
    }

    printf("\n\nDaftar Antrian Customer Service:\n");
    if (!isEmpty(2)) {
        for (int i = headCS; i <= tailCS; i++) {
            if (i == headCS) strcpy(csQueue[i].status, "Sedang Diproses");
            printf("\nNomor Antrian: %d", csQueue[i].nomor_antrian);
            printf("\nID Nasabah: %d", csQueue[i].id_nasabah);
            printf("\nNama Nasabah: %s", csQueue[i].nama_nasabah);
            printf("\nJenis Layanan: %s", csQueue[i].jenis_layanan);
            printf("\nWaktu Kedatangan: %s", csQueue[i].waktu_kedatangan);
            printf("\nStatus: %s", csQueue[i].status);
            printf("\n------------------------");
        }
    } else {
        printf("\nAntrian Customer Service kosong!");
    }
}

void Clear() {
    headTeller = tailTeller = headCS = tailCS = -1;
    nomorAntrianLayanan[0] = nomorAntrianLayanan[1] = 0;
    printf("\nAntrian Dikosongkan!\n");
}

void checkQueueStatus() {
    int pilihan;
    printf("\nPilih Antrian untuk Dicek Statusnya (1: Teller, 2: Customer Service): ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        printf("\nStatus Antrian Teller:\n");
        if (isEmpty(1)) {
            printf("Antrian Teller kosong.\n");
        } else if (isFull(1)) {
            printf("Antrian Teller sudah penuh.\n");
        } else {
            printf("Antrian Teller tidak kosong dan tidak penuh.\n");
        }
    } else if (pilihan == 2) {
        printf("\nStatus Antrian Customer Service:\n");
        if (isEmpty(2)) {
            printf("Antrian Customer Service kosong.\n");
        } else if (isFull(2)) {
            printf("Antrian Customer Service sudah penuh.\n");
        } else {
            printf("Antrian Customer Service tidak kosong dan tidak penuh.\n");
        }
    } else {
        printf("\nPilihan tidak valid!\n");
    }
}

void displayAllCustomers() {
    printf("\nDaftar Semua Nasabah dalam Antrian:\n");
    PeekAll();
}

int menu() {
    int pilihan;
    printf("\nPROGRAM ANTRIAN BANK\n\n");
    PeekAll();
    printf("\n\nMENU\n1. Masukkan Antrian\n"
           "2. Antrian Selesai\n"
           "3. Kosongkan Antrian\n"
           "4. Cek Status Antrian\n"
           "5. Tampilkan Semua Nasabah\n"
           "6. Exit\n"
           "Pilih: ");
    scanf("%d", &pilihan);
    return pilihan;
}
