#ifndef INC_VECTOR_H
#define INC_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

// возвращает пустой вектор, в который можно вставить n элементов
vector createVector(size_t n);

// изменяет количество памяти, выделенное под хранение элементов вектора
void reserve(vector *v, size_t newCapacity);

//освобождает память, выделенную под неиспользуемые элементы
void shrinkToFit(vector *v);

// возвращает 'истина' если вектор полный, иначе - 'ложь'
bool isFull(vector *v);

// добавляет в конец вектора число x
void pushBack(vector *v, int x);

#endif
