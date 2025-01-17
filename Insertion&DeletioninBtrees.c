#include <stdio.h>
#include <stdlib.h>

#define ORDER 3

typedef struct BPlusTreeNode {
    int keys[ORDER - 1];
    struct BPlusTreeNode *children[ORDER];
    int numKeys;
    int isLeaf;
} BPlusTreeNode;

BPlusTreeNode *createNode(int isLeaf) {
    BPlusTreeNode *newNode = (BPlusTreeNode *)malloc(sizeof(BPlusTreeNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    for (int i = 0; i < ORDER; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}


void Print_Tree(BPlusTreeNode *root, int level) {
    if (root == NULL) return;
    printf("Level %d: ", level);
    for (int i = 0; i < root->numKeys; i++) {
        printf("%d ", root->keys[i]);
    }
    printf("\n");
    if (!root->isLeaf) {
        for (int i = 0; i <= root->numKeys; i++) {
            Print_Tree(root->children[i], level + 1);
        }
    }
}

void splitChild(BPlusTreeNode *parent, int i, BPlusTreeNode *child) {
    BPlusTreeNode *newChild = createNode(child->isLeaf);
    newChild->numKeys = (ORDER - 1) / 2;

    for (int j = 0; j < (ORDER - 1) / 2; j++) {
        newChild->keys[j] = child->keys[j + (ORDER + 1) / 2 - 1];
    }
    if (!child->isLeaf) {
        for (int j = 0; j <= (ORDER - 1) / 2; j++) {
            newChild->children[j] = child->children[j + (ORDER + 1) / 2 - 1];
        }
    }
    child->numKeys = (ORDER - 1) / 2;

    for (int j = parent->numKeys; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChild;

    for (int j = parent->numKeys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = child->keys[(ORDER - 1) / 2];
    parent->numKeys++;
}

void insertNonFull(BPlusTreeNode *node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == ORDER - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(BPlusTreeNode **root, int key) {
    BPlusTreeNode *r = *root;
    if (r->numKeys == ORDER - 1) {
        BPlusTreeNode *s = createNode(0);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, key);
    } else {
        insertNonFull(r, key);
    }
}

void deleteKey(BPlusTreeNode **root, int key) {
    BPlusTreeNode *r = *root;
    if (r == NULL) return;

    int i = 0;
    while (i < r->numKeys && key > r->keys[i]) {
        i++;
    }

    if (i < r->numKeys && key == r->keys[i]) {
        if (r->isLeaf) {
            for (int j = i; j < r->numKeys - 1; j++) {
                r->keys[j] = r->keys[j + 1];
            }
            r->numKeys--;
        } else {
            BPlusTreeNode *pred = r->children[i];
            while (!pred->isLeaf) {
                pred = pred->children[pred->numKeys];
            }
            int predKey = pred->keys[pred->numKeys - 1];
            deleteKey(&(r->children[i]), predKey);
            r->keys[i] = predKey;
        }
    } else if (!r->isLeaf) {
        deleteKey(&(r->children[i]), key);
    }

    if (r->numKeys == 0 && !r->isLeaf) {
        *root = r->children[0];
        free(r);
    }
}

int main() {
    BPlusTreeNode *root = createNode(1);
    int keysToInsert[] = {5, 15, 25, 35, 45, 55, 40, 20, 30};
    int numKeysToInsert = sizeof(keysToInsert) / sizeof(keysToInsert[0]);

    for (int i = 0; i < numKeysToInsert; i++) {
        insert(&root, keysToInsert[i]);
    }

    printf("B+ Tree after inserting all keys:\n");
    Print_Tree(root, 0);

    int keysToDelete[] = {40, 5, 45, 35, 25, 55};
    int numKeysToDelete = sizeof(keysToDelete) / sizeof(keysToDelete[0]);

   
   
    for (int i = 0; i < numKeysToDelete; i++) {
    deleteKey(&root, keysToDelete[i]);
    printf("\nB+ Tree after deleting key %d:\n", keysToDelete[i]);
    Print_Tree(root, 0);
                 }

   
   
   
   
    return 0;
}