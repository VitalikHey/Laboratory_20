#include "vector.h"


vector createVector(size_t n){
    vector new;

    if (n == 0){
        new.data = NULL;
    } else {
        new.data = (int *) malloc(n * sizeof(int));
    }

    new.size = 0;
    new.capacity = n;

    return new;
}


void reserve(vector *v, size_t newCapacity){
    if (newCapacity == 0){
        v->data = NULL;
    } else {
        v->data = (int *)realloc(v->data, sizeof(int) * newCapacity);
    }

    v->size = v->size > newCapacity ? newCapacity : v->size;
    v->capacity = newCapacity;
}


void shrinkToFit(vector *v){
    if (v->capacity > v->size){
        v->data = (int *)realloc(v->data, sizeof(int) * v->size);
        v->capacity = v->size;
    }
}


bool isFull(vector *v){
    return v->size == v->capacity;
}


void pushBack(vector *v, int x){
    if (!v->capacity){
        reserve(v, 1);
    } else if (isFull(v)){
        reserve(v, v->capacity * 2);
    }

    v->data[v->size++] = x;
}
