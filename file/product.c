#include "product.h"

product readProductDataFromBinFile(FILE *file){
    product data;
    fread(&data, sizeof(product), 1, file);
    return data;
}


product* readProductsFromBinFile(char *fileName, size_t *productsQuantity){
    FILE *file = openFile(fileName, "rb");

    fread(productsQuantity, sizeof(size_t), 1, file);
    product *buffer = malloc(*productsQuantity * sizeof(product));
    for (size_t i = 0; i < *productsQuantity; i++){
        buffer[i] = readProductDataFromBinFile(file);
    }
    fclose(file);
    return buffer;
}


order readOrderDataFromBinFile(FILE *file){
    order data;
    fread(&data, sizeof(order), 1, file);
    return data;
}


void writeProductsToBinFile(char *fileName, product *productsArr,
                        size_t productsQuantity){
    FILE *file = openFile(fileName, "wb");
    fwrite(&productsQuantity, sizeof(size_t), 1, file);

    for (size_t i = 0; i < productsQuantity; i++){
        fwrite(&productsArr[i], sizeof(product), 1, file);
    }

    fclose(file);
}


size_t searchProductIndexInArray(char *productName, product *productsArr,
                                 size_t size){
    for (size_t i = 0; i < size; i++){
        if (strcmp(productName, productsArr[i].name) == 0){
            return i;
        }
    }
    printf("Нет продукта с таким именем");
    return -1;
}


order* readOrdersFromBinFile(char *fileName, size_t *ordersQuantity){
    FILE *file = openFile(fileName, "rb");

    fread(ordersQuantity, sizeof(size_t), 1, file);
    order *buffer = malloc(*ordersQuantity * sizeof(order));
    for (size_t i = 0; i < *ordersQuantity; i++){
        buffer[i] = readOrderDataFromBinFile(file);
    }

    fclose(file);
    return buffer;
}


void writeOrdersToBinFile(char *fileName, order *ordersArr, size_t ordersQuantity){
    FILE *file = openFile(fileName, "wb");

    fwrite(&ordersQuantity, sizeof(size_t), 1, file);

    for (size_t i = 0; i < ordersQuantity; i++){
        fwrite(&ordersArr[i], sizeof(order), 1, file);
    }

    fclose(file);
}


void writeAvailableProductsInBinFile(char *fileName, product *productsArr,
                               size_t productsQuantity, size_t notAvailableProductsQuantity){
    FILE *file = openFile(fileName, "wb");
    size_t availableProductsQuantity = productsQuantity - notAvailableProductsQuantity;
    fwrite(&availableProductsQuantity, sizeof(size_t), 1, file);

    for (size_t i = 0; i < productsQuantity; i++){
        if (productsArr[i].quantity > 0){
            fwrite(&productsArr[i], sizeof(product), 1, file);
        }
    }
    fclose(file);
}