#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE_LEN 256
#define DATABASE_FILE "database.txt"

typedef struct KVPair {
    int key;
    char value[MAX_VALUE_LEN];
    struct KVPair *next;
} KVPair;
void put(KVPair **head, int key, const char *value);
char* get(KVPair *head, int key);
void delete(KVPair **head, int key);
void clear(KVPair **head);
void loadDatabase(KVPair **head);
void saveDatabase(KVPair *head);
void printAll(KVPair *head);

void loadDatabase(KVPair **head) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) {
        perror("Error opening database file");
        return;
    }

    char line[MAX_VALUE_LEN + 10];
    while (fgets(line, sizeof(line), file)) {
        int key;
        char value[MAX_VALUE_LEN];
        if (sscanf(line, "%d,%255[^\n]", &key, value) == 2) {
            put(head, key, value);
        }
    }
    fclose(file);
}
void saveDatabase(KVPair *head) {
    FILE *file = fopen(DATABASE_FILE, "w");
    if (!file) {
        perror("Error opening database file");
        return;
    }

    KVPair *current = head;
    while (current) {
        fprintf(file, "%d,%s\n", current->key, current->value);
        current = current->next;
    }
    fclose(file);
}
void put(KVPair **head, int key, const char *value) {
    KVPair *current = *head;
    while (current) {
        if (current->key == key) {
            strncpy(current->value, value, MAX_VALUE_LEN);
            return; 
        }
        current = current->next;
    }
    KVPair *newPair = (KVPair *)malloc(sizeof(KVPair));
    if (!newPair) {
        perror("Error allocating memory");
        exit(1);
    }
    newPair->key = key;
    strncpy(newPair->value, value, MAX_VALUE_LEN);
    newPair->next = *head;
    *head = newPair;
}
char* get(KVPair *head, int key) {
    KVPair *current = head;
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}
void delete(KVPair **head, int key) {
    KVPair *current = *head;
    KVPair *prev = NULL;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("%d not found\n", key);
}
void clear(KVPair **head) {
    KVPair *current = *head;
    while (current) {
        KVPair *next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}
void printAll(KVPair *head) {
    KVPair *current = head;
    while (current) {
        printf("%d,%s\n", current->key, current->value);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    KVPair *head = NULL; 
    loadDatabase(&head);

    for (int i = 1; i < argc; i++) {
        char *command = argv[i];
        char *cmdType = strsep(&command, ",");

        if (strcmp(cmdType, "p") == 0) {
            int key = atoi(strsep(&command, ","));
            const char *value = strsep(&command, ",");
            put(&head, key, value);
        } else if (strcmp(cmdType, "g") == 0) {
            int key = atoi(strsep(&command, ","));
            char *value = get(head, key);
            if (value) {
                printf("%d,%s\n", key, value);
            } else {
                printf("%d not found\n", key);
            }
        } else if (strcmp(cmdType, "d") == 0) {
            int key = atoi(strsep(&command, ","));
            delete(&head, key);
        } else if (strcmp(cmdType, "c") == 0) {
            clear(&head);
        } else if (strcmp(cmdType, "a") == 0) {
            printAll(head);
        } else {
            printf("bad command\n");
        }
    }
    saveDatabase(head);
    clear(&head);
    return 0;
}
