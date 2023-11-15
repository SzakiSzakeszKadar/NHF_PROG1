#ifndef MATRIX_LETREHOZAS_H
#define MATRIX_LETREHOZAS_H
//A M�trix strukt�ra ami t�rolja egy m�trix adatait.
typedef struct Matrix{
    int sorok;
    int oszlopok;
    double** adat;
} Matrix;
Matrix* matrix_letrehozasa(int sorok, int oszlopok);
void matrix_felszabaditasa(Matrix* matrix);
#endif
