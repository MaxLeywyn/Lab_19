#ifndef LAB_19_PRODUCT_H
#define LAB_19_PRODUCT_H

#include <stdio.h>
#include "file.h"

typedef struct product{
    char* name;
    size_t unitPrice;
    size_t fullPrice;
    size_t quantity;
} product;

typedef struct order{
    char* name;
    size_t quantity;
} order;

product* readProductsFromBinFile(char *fileName, size_t *productsQuantity);


void writeProductsToBinFile(char *fileName, product *productsArr,
                            size_t productsQuantity);

void writeAvailableProductsInBinFile(char *fileName, product *productsArr,
                                     size_t productsQuantity, size_t notAvailableProductsQuantity);

size_t searchProductIndexInArray(char *productName, product *productsArr,
                                 size_t size);

order* readOrdersFromBinFile(char *fileName, size_t *ordersQuantity);

void writeOrdersToBinFile(char *fileName, order *ordersArr, size_t ordersQuantity);

#endif //LAB_19_PRODUCT_H
