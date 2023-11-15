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
    Masolatot keszit egy matrixrol es visszater vele
*/
Matrix* matrix_masolasa(Matrix* eredeti) {
    if (eredeti == NULL) return NULL;
    int sorok = eredeti->sorok;
    int oszlopok = eredeti->oszlopok;
    Matrix* masolat = matrix_letrehozasa(sorok, oszlopok);
    if (masolat == NULL) return NULL;
    for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < oszlopok; j++) {
            masolat->adat[i][j] = eredeti->adat[i][j];
        }
    }
    return masolat;
}
/*
    A fuggveny ket matrix osszeget adja vissza, vizsgalva hogy a muvelet elvegezheto-e
*/
Matrix* matrixok_osszeadasa(Matrix* a, Matrix* b){
    if (a->sorok != b->sorok || a->oszlopok != b->oszlopok) {
        printf("\nHIBA A matrixok meretei nem kompatibilisek, igy az osszeadas nem vegezheto el.\n");
        return NULL;
    }
    int sorok = a->sorok;
    int oszlopok = a->oszlopok;
    Matrix* eredmeny = matrix_letrehozasa(sorok, oszlopok);
    for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < oszlopok; j++) {
            eredmeny->adat[i][j] = a->adat[i][j] + b->adat[i][j];
        }
    }
    return eredmeny;
}
/*
    A fuggveny ket matrix  kulonbseget adja vissza, vizsgalva hogy a muvelet elvegezheto-e
*/
Matrix* matrixok_kivonasa(Matrix* a, Matrix* b){
    if (a->sorok != b->sorok || a->oszlopok != b->oszlopok) {
        printf("\nHIBA A matrixok meretei nem kompatibilisek, igy a kivonas nem vegezheto el.\n");
        return NULL;
    }
    int sorok = a->sorok;
    int oszlopok = a->oszlopok;
    Matrix* eredmeny = matrix_letrehozasa(sorok, oszlopok);
    for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < oszlopok; j++) {
            eredmeny->adat[i][j] = a->adat[i][j] - b->adat[i][j];
        }
    }
    return eredmeny;
}
/*
    A fuggveny ket matrix szorzatat adja vissza, vizsgalva hogy a muvelet elvegezheto-e
*/
Matrix* matrixok_szorzasa(Matrix* a, Matrix* b) {
    if (a->oszlopok != b->sorok) {
        printf("\n HIBA:  A matrixok meretei nem kompatibilisek, igy a szorzas nem vegezheto el.\n");
        return NULL;
    }
    int sorok = a->sorok;
    int oszlopok = b->oszlopok;
    Matrix* eredmeny = matrix_letrehozasa(sorok, oszlopok);
    for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < oszlopok; j++) {
            eredmeny->adat[i][j] = 0.0;
            for (int k = 0; k < a->oszlopok; k++) {
                eredmeny->adat[i][j] += a->adat[i][k] * b->adat[k][j];
            }
        }
    }
    return eredmeny;
}
/*
    A fuggveny egy matrix transzponaltjat adja vissza
*/
Matrix* matrix_transzponalasa(Matrix* a) {
    int sorok = a->sorok;
    int oszlopok = a->oszlopok;
    Matrix* eredmeny = matrix_letrehozasa(oszlopok, sorok);
    for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < oszlopok; j++) {
            eredmeny->adat[j][i] = a->adat[i][j];
        }
    }
    return eredmeny;
}
/*
    A fuggveny a Gauss eliminacios segitsegevel vegzi el az also haromszog alakba rendezest.
*/
void Gauss_Eliminacio_det_rang(Matrix *a) {
    int n = a->sorok;
    int m = a->oszlopok;
    for (int i = 0; i < n; i++) {
        int nem_nulla_sor = -1;
        for (int k = i; k < n; k++) {
            if (a->adat[k][i] != 0.0) {
                nem_nulla_sor = k;
                break;
            }
        }
        if (nem_nulla_sor == -1) {
            return;
        }
        if (nem_nulla_sor != i) {
            for (int j = 0; j < m; j++) {
                double temp = a->adat[i][j];
                a->adat[i][j] = a->adat[nem_nulla_sor][j];
                a->adat[nem_nulla_sor][j] = temp;
            }
        }
        for (int k = i + 1; k < n; k++) {
            double factor = a->adat[k][i] / a->adat[i][i];
            for (int j = i; j < m; j++) {
                a->adat[k][j] -= factor * a->adat[i][j];
            }
        }
    }
}
/*
    A  fuggveny ket sor cserejet hajtja vegre egy matrixban
*/
void sorok_csereje(Matrix* matrix, int sor1, int sor2) {
    double* temp = matrix->adat[sor1];
    matrix->adat[sor1] = matrix->adat[sor2];
    matrix->adat[sor2] = temp;
}
/*
    A fuggveny egy adott sor elemeit leosztja egy matrixban a megadott osztoval
*/
void sorok_osztasa(Matrix* matrix, int sor, double oszto) {
    for (int j = 0; j < matrix->oszlopok; j++) {
        matrix->adat[sor][j] /= oszto;
    }
}
/*
    A fuggveny egy cel sorbol vonja ki a forras sor elemeinek faktorszorosat egy matrixban
*/
void sorok_kivonasa(Matrix* matrix, int celSor, int forrasSor, double faktor) {
    for (int j = 0; j < matrix->oszlopok; j++) {
        matrix->adat[celSor][j] -= faktor * matrix->adat[forrasSor][j];
    }
}
/*
    A fuggveny a Gauss eliminacioval  szamolja ki egy matrix inverzet es a lin. egyenlet megoldasait.
*/
void Gauss_Eliminacio_inverz(Matrix* a,  Matrix* I) {
    int n = a->sorok;
    for (int i = 0; i < n; i++) {
        int pivotSor = i;
        double pivot = a->adat[i][i];
        for (int j = i + 1; j < n; j++) {
            if (a->adat[j][i] > pivot) {
                pivot = a ->adat[j][i];
                pivotSor = j;
            }
        }
        if (pivotSor != i) {
            sorok_csereje(a, pivotSor, i);
            sorok_csereje(I, pivotSor, i);
        }

        double pivot_ertek = a -> adat[i][i];
        sorok_osztasa(a, i, pivot_ertek);
        sorok_osztasa(I, i, pivot_ertek);

        for (int j = i + 1; j < n; j++) {
            double faktor = a->adat[j][i];
            sorok_kivonasa(a, j, i, faktor);
            sorok_kivonasa(I, j, i, faktor);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double faktor = a->adat[j][i];
            sorok_kivonasa(I, j, i, faktor);
        }
    }
}
/*
    A fuggveny az elozo fuggveny segitsegevel szamolja ki egy negyzetes matrix inverzet es vissza is ter vele.
*/
Matrix* inverz_matrix(Matrix* a) {
    int n = a->sorok;
    Matrix* I = matrix_letrehozasa(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                I->adat[i][j] = 1.0;
            } else {
                I->adat[i][j] = 0.0;
            }
        }
    }
    Gauss_Eliminacio_inverz(a, I);
    return I;
}
// Fuggveny, amely megoldja a linearis egyenletrendszert Ax = b, ahol A az eredeti matrix, x a megoldas es b a szabadtagok
void Gauss_Megoldas(Matrix* a, double* b, double* x) {
    int n = a->sorok;
    Matrix* I = inverz_matrix(a);
    double* tmp = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        tmp[i] = 0.0;
        for (int j = 0; j < n; j++) {
            tmp[i] += I->adat[i][j] * b[j];
        }
    }
    for (int i = 0; i < n; i++) {
        x[i] = tmp[i];
    }
    free(tmp);
    matrix_felszabaditasa(I);
}
/*
    A fuggveny kiszamolja egy negyzetes matrix nyomat
*/
double matrix_nyoma(Matrix *a){
    double tr=0;
    if(a->sorok != a->oszlopok){
        printf("\n HIBA: A matrix nem negyzetes, nyom nem szamithato \n");
        return -1;
    }
    for(int i = 0;i < a->sorok;i++){
        tr += a->adat[i][i];
    }
    return tr;
}
/*
    A fuggveny kiszamolja egy negyzetes matrix determinansat es visszatlr azzal
*/
double determinans_szamitas(Matrix *a){
    double det = 1.0;
    Gauss_Eliminacio_det_rang(a);
    for(int i=0;i<a->sorok;i++){
            det=det*a->adat[i][i];
        }
    return det;
}
/*
    A fuggveny kiszamolja egy negyzetes matrix rangjat es visszater azzal
*/
int matrix_rangja(Matrix* a){
   Gauss_Eliminacio_det_rang(a);
   int rang = 0;
    for (int i = 0; i < a->sorok; i++) {
        bool nullaSor = true;
        for (int j = 0; j < a->oszlopok && nullaSor; j++) {
            if (a->adat[i][j] != 0.0) {
                nullaSor = false;
            }
        }
        if (!nullaSor) {
            rang++;
        }
    }
    return rang;
}















