#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ba�l� liste d���m� i�in yap� tan�m�
typedef struct SyslogNode {
    char *log;
    struct SyslogNode *next;
} SyslogNode;

// Yeni bir d���m olu�turma fonksiyonu
SyslogNode* createNode(char *log) {
    SyslogNode *newNode = (SyslogNode*)malloc(sizeof(SyslogNode));
    newNode->log = strdup(log);
    newNode->next = NULL;
    return newNode;
}

// Ba�l� listeye d���m ekleme fonksiyonu
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

// Ba�l� listeyi ekrana yazd�rma fonksiyonu
void printList(SyslogNode *head) {
    SyslogNode *temp = head;
    while (temp != NULL) {
        printf("Log Kaydi: %s\n", temp->log); // T�rk�e a��klama
        temp = temp->next;
    }
}

// Ba�l� listeyi serbest b�rakma fonksiyonu
void freeList(SyslogNode *head) {
    SyslogNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->log);
        free(temp);
    }
}

// Syslog dosyas�n� okuma ve loglar� ba�l� listeye ekleme fonksiyonu
void readSyslog(SyslogNode **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Syslog dosyasini acma hatasi"); // Hata mesaj� T�rk�ele�tirildi
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Sat�r sonu karakterini kald�r
        line[strcspn(line, "\n")] = '\0';
        appendNode(head, line);
    }

    fclose(file);
}

int main() {
    SyslogNode *syslogList = NULL;

    // Syslog dosyas�n� oku ve loglar� ba�l� listeye ekle
    readSyslog(&syslogList, "/var/log/syslog");

    // Ba�l� listeyi yazd�r
    printf("Syslog Kayitlari:\n"); // T�rk�e ��kt�
    printList(syslogList);

    // Ba�l� listeyi serbest b�rak
    freeList(syslogList);

    return 0;
}

