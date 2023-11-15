#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "matrix_letrehozas.h"
#include "matrix_muveletek.h"
#include "fomenu.h"
#include "menupontok.h"
#include "matrix_beolvasas.h"
#include "matrix_kiiratas.h"
#include "debugmalloc.h"
/*
    Memoriateruletet foglal egy matrixnak, amelynek meretet a sorok es oszlopok szamaval hatarozza meg.
    Hibak eseten jelzi a memoriafoglalassal kapcsolatos problemakat.
*/
Matrix* matrix_letrehozasa(int sorok, int oszlopok) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (matrix == NULL)printf("\nHIBA: Nem sikerult memoriat lefoglalni a matixnak.\n");
    matrix->sorok = sorok;
    matrix->oszlopok = oszlopok;
    matrix->adat = (double**)malloc(sorok * sizeof(double*));
    if (matrix->adat == NULL) {
        printf("\nHIBA: Nem sikerult memoriat foglalni a matrix elemeinek.\n");
        free(matrix);
    }
    for (int i = 0; i < sorok; i++) {
        matrix->adat[i] = (double*)malloc(oszlopok * sizeof(double));
        if (matrix->adat[i] == NULL) {
            printf("\nHIBA: Nem sikerult memoriat lefoglalni a matrix elemeinek.\n");
            for (int j = 0; j < i; j++) {
                free(matrix->adat[j]);
            }
            free(matrix->adat);
            free(matrix);
        }
    }
    return matrix;
}
/*
    Ez a fuggveny a dinamikusan foglalt memoria felszabadítasat vegzi egy matrixnak,
    elõször a sorok elemeit, majd a sorokat tartalmazo tömböt, es vegul magat a matrixot.
*/
void matrix_felszabaditasa(Matrix* matrix) {
    for (int i = 0; i < matrix->sorok; i++) {
        free(matrix->adat[i]);
    }
    free(matrix->adat);
    free(matrix);
}


