#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

int hash_table[TABLE_SIZE];

void initialize_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = -1;
    }
}

int hash_function(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) {
    int index = hash_function(key);
    int i = 0;
    while (hash_table[(index + i * i) % TABLE_SIZE] != -1) {
        i++;
    }
    hash_table[(index + i * i) % TABLE_SIZE] = key;
}

void display_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == -1) {
            printf("Empty\n");
        } else {
            printf("%d\n", hash_table[i]);
        }
    }
}

int main() {
    initialize_table();
    int keys[] = {9, 19, 29, 39, 49, 59, 71};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insert(keys[i]);
    }

    display_table();

    return 0;
}
