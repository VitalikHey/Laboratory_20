#include "node.h"


node *createNode(int k) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = k;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


node* insert(node *p, int k, bool isLeft) {
    node *newNode = createNode(k);
    if (isLeft)
        p->left = newNode;
    else
        p->right = newNode;

    return newNode;
}