#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>


struct node {
    int value;
    struct node *left;
    struct node *right;
};


struct node *nodeCreate(int value) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


struct node *insertNode(struct node *root, int value) {
    if (root == NULL) {
        return nodeCreate(value);
    }
    if (value < root->value) {
        root->left = insertNode(root->left, value);
    } else if (value > root->value) {
        root->right = insertNode(root->right, value);
    }
    return root;
}


struct node *minuimumValue(struct node *node) {
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}


struct node *deleteNode(struct node *root, int value) {
    if (root == NULL) return root;

    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct node *tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL) {
            struct node *tmp = root->left;
            free(root);
            return tmp;
        }

        struct node *tmp = minuimumValue(root->right);
        root->value = tmp->value;
        root->right = deleteNode(root->right, tmp->value);
    }
    return root;
}


int height(struct node *node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


int vine(struct node *grand) {
    int count = 0;
    struct node *tmp = grand->right;

    while (tmp != NULL) {
        if (tmp->left != NULL) {
            struct node *oldTmp = tmp;
            tmp = tmp->left;
            oldTmp->left = tmp->right;
            tmp->right = oldTmp;
            grand->right = tmp;
        } else {
            count++;
            grand = tmp;
            tmp = tmp->right;
        }
    }
    return count;
}

 
void compress(struct node *grand, int m) {
    struct node *tmp = grand->right;
	int i =0;
    for ( i = 0; i < m; i++) {
        struct node *oldTmp = tmp;
        tmp = tmp->right;
        grand->right = tmp;
        oldTmp->right = tmp->left;
        tmp->left = oldTmp;
        grand = tmp;
        tmp = tmp->right;
    }
}


int logBase2(int N) {
    return (int)(log(N) / log(2));
}


struct node *dswfunc(struct node *root) {
    struct node *grand = nodeCreate(0);
    grand->right = root;

    int count = vine(grand);
    int h = logBase2(count + 1);
    int m = (int)pow(2, h) - 1;

    compress(grand, count - m);

    for (m = m / 2; m > 0; m /= 2) {
        compress(grand, m);
    }

    struct node *balancedRoot = grand->right;
    free(grand);
    return balancedRoot;
}


int main() {
    struct node *root = NULL;
    int Q;
    scanf("%d", &Q);
	
	int i =0;
    for (i = 0; i < Q; i++) {
        char input[10];
        int value;
      
        scanf("%s", input);


        if (strcmp(input, "insert") == 0) {
            scanf("%d", &value);
            root = insertNode(root, value);
        } else if (strcmp(input, "delete") == 0) {
            scanf("%d", &value);
            root = deleteNode(root, value);
        } else if (strcmp(input, "balance") == 0) {
            root = dswfunc(root);
        } else if (strcmp(input, "height") == 0) {
            printf("%d\n", height(root));
        }
    }

    return 0;
}
