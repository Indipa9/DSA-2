#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 8

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
    while (hash_table[index] != -1) {
        index = (index + 1) % TABLE_SIZE;
    }
    hash_table[index] = key;
}

int search(int key) {
    int index = hash_function(key);
    int start_index = index;
    while (hash_table[index] != key) {
        index = (index + 1) % TABLE_SIZE;
        if (index == start_index || hash_table[index] == -1) {
            return -1;
        }
    }
    return index;
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
    int keys[] = {12, 5, 20, 16, 8, 4, 18};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insert(keys[i]);
    }

    display_table();

    int key_to_search = 20;
    int result = search(key_to_search);
    if (result != -1) {
        printf("Key %d found at index %d\n", key_to_search, result);
    } else {
        printf("Key %d not found\n", key_to_search);
    }

    return 0;
}
