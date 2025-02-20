#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Baðlý liste düðümü için yapý tanýmý
typedef struct SyslogNode {
    char *log;
    struct SyslogNode *next;
} SyslogNode;

// Yeni bir düðüm oluþturma fonksiyonu
SyslogNode* createNode(char *log) {
    SyslogNode *newNode = (SyslogNode*)malloc(sizeof(SyslogNode));
    newNode->log = strdup(log);
    newNode->next = NULL;
    return newNode;
}

// Baðlý listeye düðüm ekleme fonksiyonu
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

// Baðlý listeyi ekrana yazdýrma fonksiyonu
void printList(SyslogNode *head) {
    SyslogNode *temp = head;
    while (temp != NULL) {
        printf("Log Kaydi: %s\n", temp->log); // Türkçe açýklama
        temp = temp->next;
    }
}

// Baðlý listeyi serbest býrakma fonksiyonu
void freeList(SyslogNode *head) {
    SyslogNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->log);
        free(temp);
    }
}

// Syslog dosyasýný okuma ve loglarý baðlý listeye ekleme fonksiyonu
void readSyslog(SyslogNode **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Syslog dosyasini acma hatasi"); // Hata mesajý Türkçeleþtirildi
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Satýr sonu karakterini kaldýr
        line[strcspn(line, "\n")] = '\0';
        appendNode(head, line);
    }

    fclose(file);
}

int main() {
    SyslogNode *syslogList = NULL;

    // Syslog dosyasýný oku ve loglarý baðlý listeye ekle
    readSyslog(&syslogList, "/var/log/syslog");

    // Baðlý listeyi yazdýr
    printf("Syslog Kayitlari:\n"); // Türkçe çýktý
    printList(syslogList);

    // Baðlý listeyi serbest býrak
    freeList(syslogList);

    return 0;
}

