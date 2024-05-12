#include "vector.h"


vector createVector(size_t n) {
    int *new_data = (int *) malloc(n * sizeof(int));
    if (new_data == NULL) {
        fprintf(stderr, "bad realloc");
        exit(1);
    }
    return (vector) {new_data, 0, n};
}


void shrinkToFit(vector *v) {
    if (v->size < v->capacity) {
        int *new_data = (int *) realloc(v->data, v->size * sizeof(int));
        if (new_data == NULL) {
            fprintf(stderr, "bad realloc");
            exit(1);
        }
        v->data = new_data;
        v->capacity = v->size;
    }
}


void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
        return;
    }

    int *new_data = (int *) realloc(v->data, newCapacity * sizeof(int));

    if (new_data == NULL) {
        fprintf(stderr, "bad realloc");
        exit(1);
    }
    if (v->size > newCapacity) {
        v->size = newCapacity;
    }
    v->data = new_data;
    v->capacity = newCapacity;
}


void clear(vector *v) {
    v->size = 0;
}


void deleteVector(vector *v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}


bool isEmpty(vector *v) {
    return v->size == 0;
}


bool isFull(vector *v) {
    return v->size == v->capacity;
}


int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}


void pushBack(vector *v, int x) {
    if (isFull(v)) {
        if (v->capacity != 0)
            reserve(v, v->capacity * 2);
        else
            reserve(v, v->capacity + 1);
    }
    v->data[v->size] = x;
    v->size++;
}


void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    v->size--;
    v->data[v->size] = 0;

}


int *atVector(vector *v, size_t index) {
    if (index > v->size - 1) {
        fprintf(stderr, "IndexError: a [%zu] is not exists", index);
        exit(1);
    }
    return &v->data[index];
}


int *back(vector *v) {
    return atVector(v, v->size - 1);
}


int *front(vector *v) {
    return atVector(v, 0);
}