#ifndef INC_NODE_H
#define INC_NODE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

// создает дерево с ключом k
node *createNode(int k);

// вставляет ключ k в дерево с корнем p и возвращает новое дерево
node* insert(node *p, int k, bool isLeft);

#endif
