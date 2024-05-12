#include "polynom.h"

Polynom createPolynomFromArray(int *powers, double *coefficients, int argsQuantity){
    Polynom p;
    p.monomialQuantity = argsQuantity;
    p.data = (Monomial *) malloc(argsQuantity * sizeof(Monomial));

    for (int i = 0; i < argsQuantity; ++i) {
        p.data[i].coefficients = coefficients[i];
        p.data[i].power = powers[i];
    }

    return p;
}


Polynom* createPolynomsFromArray(int *powers, double *coefficients,
                                       int *monQuantity, int polQuantity){
    Polynom *buffer = malloc(polQuantity * sizeof(Polynom));
    for (int i = 0; i < polQuantity; i++) {
        buffer[i] = createPolynomFromArray(
                powers, coefficients, monQuantity[i]);

        powers += monQuantity[i];
        coefficients += monQuantity[i];
    }

    return buffer;
}


Polynom loadPolynomFromFile(FILE *f){
    Polynom p;

    fread(&p, sizeof(Polynom), 1, f);
    p.data = (Monomial *) malloc(p.monomialQuantity * sizeof (Monomial));
    fread(p.data, sizeof (Monomial), p.monomialQuantity, f);

    return p;
}


Polynom* loadPolynomsFromFile(FILE *f, int *polQuantity){
    fread(polQuantity, sizeof (int), 1, f);

    Polynom *buffer = malloc(*polQuantity * sizeof(Polynom));
    for (int i = 0; i < *polQuantity; i++) {
        buffer[i] = loadPolynomFromFile(f);
    }
    return buffer;
}


void savePolynomToFile(Polynom p, FILE *f){
    fwrite(&p, sizeof(Polynom), 1, f);
    fwrite(p.data, sizeof (Monomial), p.monomialQuantity, f);
}


void savePolynomsToFile(Polynom *ps, FILE *f, int polQuantity){
    fwrite(&polQuantity, sizeof (int), 1, f);

    for (int i = 0; i < polQuantity; i++) {
        savePolynomToFile(ps[i], f);
    }
}


double calculatePolynomByX(Polynom p, double x){
    double result = 0;
    double mul = 1;
    int index = p.monomialQuantity - 1;

    for (int power = 0; power <= p.data[0].power; power++){
        if (p.data[index].power == power) {
            result += p.data[index].coefficients * mul;
            index--;
        }
        mul *= x;
    }

    return result;
}

void writePolyToFile(char *fileName, int *powers, double *coefficients,
                 int *monQuantity, int polQuantity){
    Polynom *ps = createPolynomsFromArray(
            powers, coefficients,
            monQuantity, polQuantity);

    FILE *f = openFile(fileName, "wb");

    savePolynomsToFile(ps, f, polQuantity);

    fclose(f);
}

int sortedPoly(Polynom* ps, int x, int polQuantity){
    int i = 0;
    while (i < polQuantity){
        if (fabs(calculatePolynomByX(ps[i], x)) < 0.00001) {
            freePolynom(ps + i);
            ps[i] = ps[--polQuantity];
        }
        else
            i++;
    }

    return i;
}

void savePolyResult(char *fileName, Polynom *ps, int polQuantity){
    FILE* file = openFile(fileName, "wb");
    savePolynomsToFile(ps, file, polQuantity);
    fclose(file);
}

Polynom* readPolyFromFile(char *fileName){
    FILE *f = openFile(fileName, "rb");
    int polQuantity;
    Polynom *ps = loadPolynomsFromFile(f, &polQuantity);
    fclose(f);
    return ps;
}

void freePolynom(Polynom * p){
    free(p->data);
    p->data = NULL;
    p->monomialQuantity = 0;
}

