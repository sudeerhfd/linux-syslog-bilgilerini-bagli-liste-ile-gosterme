#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bağlı liste düğümü için yapı tanımı
typedef struct SyslogNode {
    char *log;
    struct SyslogNode *next;
} SyslogNode;

// Yeni bir düğüm oluşturma fonksiyonu
SyslogNode* createNode(char *log) {
    SyslogNode *newNode = (SyslogNode*)malloc(sizeof(SyslogNode));
    newNode->log = strdup(log);
    newNode->next = NULL;
    return newNode;
}

// Bağlı listeye düğüm ekleme fonksiyonu
void appendNode(SyslogNode **head, char *log) {
    SyslogNode *newNode = createNode(log);
    if (*head == NULL) {
        *head = newNode;
    } else {
        SyslogNode *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Bağlı listeyi ekrana yazdırma fonksiyonu
void printList(SyslogNode *head) {
    SyslogNode *temp = head;
    while (temp != NULL) {
        printf("Log Kaydi: %s\n", temp->log); // Türkçe açıklama
        temp = temp->next;
    }
}

// Bağlı listeyi serbest bırakma fonksiyonu
void freeList(SyslogNode *head) {
    SyslogNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->log);
        free(temp);
    }
}

// Syslog dosyasını okuma ve logları bağlı listeye ekleme fonksiyonu
void readSyslog(SyslogNode **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Syslog dosyasini acma hatasi"); // Hata mesajı Türkçeleştirildi
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Satır sonu karakterini kaldır
        line[strcspn(line, "\n")] = '\0';
        appendNode(head, line);
    }

    fclose(file);
}

int main() {
    SyslogNode *syslogList = NULL;

    // Syslog dosyasını oku ve logları bağlı listeye ekle
    readSyslog(&syslogList, "/var/log/syslog");

    // Bağlı listeyi yazdır
    printf("Syslog Kayitlari:\n"); 
    printList(syslogList);

    // Bağlı listeyi serbest bırak
    freeList(syslogList);

    return 0;
}

