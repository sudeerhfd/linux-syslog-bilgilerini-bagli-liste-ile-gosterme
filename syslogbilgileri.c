#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bağlı liste düğümü için yapı tanımı
typedef struct GunlukDugum {
    char *gunluk;
    struct GunlukDugum *sonraki;
} GunlukDugum;

// Yeni bir düğüm oluşturma fonksiyonu
GunlukDugum* dugumOlustur(char *gunluk) {
    GunlukDugum *yeniDugum = (GunlukDugum*)malloc(sizeof(GunlukDugum));
    if (yeniDugum == NULL) {
        perror("Bellek tahsis hatası");
        exit(EXIT_FAILURE);
    }

    yeniDugum->gunluk = strdup(gunluk);
    if (yeniDugum->gunluk == NULL) {
        free(yeniDugum);
        perror("Bellek tahsis hatası (gunluk)");
        exit(EXIT_FAILURE);
    }

    yeniDugum->sonraki = NULL;
    return yeniDugum;
}

// Bağlı listeye düğüm ekleme fonksiyonu
void dugumEkle(GunlukDugum **bas, char *gunluk) {
    GunlukDugum *yeniDugum = dugumOlustur(gunluk);
    if (*bas == NULL) {
        *bas = yeniDugum;
    } else {
        GunlukDugum *gecici = *bas;
        while (gecici->sonraki != NULL) {
            gecici = gecici->sonraki;
        }
        gecici->sonraki = yeniDugum;
    }
}

// Bağlı listeyi ekrana yazdırma fonksiyonu
void listeYazdir(GunlukDugum *bas) {
    GunlukDugum *gecici = bas;
    while (gecici != NULL) {
        printf("Günlük Kaydı: %s\n", gecici->gunluk);
        gecici = gecici->sonraki;
    }
}

// Bağlı listeyi serbest bırakma fonksiyonu
void listeSerbestBirak(GunlukDugum *bas) {
    GunlukDugum *gecici;
    while (bas != NULL) {
        gecici = bas;
        bas = bas->sonraki;
        free(gecici->gunluk);
        free(gecici);
    }
}

// Syslog dosyasını okuma ve logları bağlı listeye ekleme fonksiyonu
void gunlukOku(GunlukDugum **bas, const char *dosyaAdi) {
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        perror("Günlük dosyasını açma hatası");
        exit(EXIT_FAILURE);
    }

    char satir[1024];
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        // Satır sonu karakterini kaldır
        satir[strcspn(satir, "\n")] = '\0';
        dugumEkle(bas, satir);
    }

    fclose(dosya);
}

int main() {
    GunlukDugum *gunlukListesi = NULL;

    // Syslog dosyasını oku ve logları bağlı listeye ekle
    gunlukOku(&gunlukListesi, "/var/log/syslog");

    // Bağlı listeyi yazdır
    printf("Günlük Kayıtları:\n");
    listeYazdir(gunlukListesi);

    // Bağlı listeyi serbest bırak
    listeSerbestBirak(gunlukListesi);

    return 0;
}
