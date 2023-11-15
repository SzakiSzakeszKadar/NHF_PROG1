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
Ez a fuggveny a felhasznalotol bekeri egy matrix sorainak es oszlopainak szamat,
majd letrehoz es kitölt egy matrixot a megadott ertekekkel.
*/
Matrix* matrix_beolvas_billzet() {
    int sorok, oszlopok;
    printf("\nRENDSZER: Hany soros matrixot hozzunk letre? ");
    sorok=beolvasInt();
    printf("\nRENDSZER: Hany oszlopos matrixot hozzunk letre? ");
    oszlopok = beolvasInt();
    Matrix* matrix = matrix_letrehozasa(sorok, oszlopok); // Elozoleg definialt letrehozo fuggveny
    if (matrix == NULL) return NULL;
    printf("\nRENDSZER: Kerlek add meg a matrix elemeinek ertekeit soronkent:\n");
    for (int i = 0; i < sorok; i++) {
        for (int j = 0; j < oszlopok; j++) {
            printf("\n[%d][%d] = ", i + 1, j + 1);
            double elem = beolvasDouble();
            matrix->adat[i][j] = elem;
        }
    }
    return matrix;
}
/*
    Ez a fuggveny egy matrixot olvas be egy fajlbol, ahol elöször a sorok es oszlopok szamat kell megadni, majd a matrix elemeinek ertekeit.
    Sikeres beolvasas eseten letrehoz egy matrixot es visszaadja azt,
    egyebkent hibat jelez, es NULL ertekkel ter vissza.
*/
Matrix* matrix_beolvas_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nHIBA: A fajl nem talalhato, vagy nem olvashato.\n");
        return NULL;
    }
    int sorok, oszlopok;
    if (fscanf(file, "%d %d", &sorok, &oszlopok) != 2) {
        printf("\nHIBA: Nem sikerult beolvasni a fajlbol.\n");
        fclose(file);
        return NULL;
    }
    Matrix* matrix = matrix_letrehozasa(sorok, oszlopok);
    for (int i = 0; i  <  sorok; i++) {
        for (int j = 0; j  < oszlopok; j++) {
            double elem;
            if (fscanf(file, "%lf", &elem) != 1) {
                matrix_felszabaditasa(matrix);
                return NULL;
            }
            matrix->adat[i][j] = elem;
        }
    }
    fclose(file);
    return matrix;
}
/*
    Ez a fuggveny egy 3x3-as matrixot hoz letre, amely harom pont koordinatait tartalmazza.
    A felhasznalotol bekeri a pontok x es y koordinatait, majd a harmadik oszlop elemeit 1-re allítja.
*/
Matrix* harom_pont_matrix(){
    Matrix *A = matrix_letrehozasa(3, 3);
    // Beolvasas a felhasznalotol
    for (int i = 0; i  <  3; i++) {
        printf("Pont %c.x = ", 'A' + i);
        A->adat[i][0] = beolvasDouble();
        printf("Pont %c.y = ", 'A' + i);
        A->adat[i][1] = beolvasDouble();
    }
    // Harmadik oszlop elemeinek beallítasa egyesekre
    for (int i = 0; i  <  3; i++) {
        A->adat[i][2] = 1;
    }
    return A;
}
/*
    A fuggveny beolvas egy egesz szamot a standard bemenetrõl.
   Sikeres beolvasas eseten visszaadja az egesz szamot, egyebkent hibat jelez es ujra bekeri a bemenetet.
*/
int beolvasInt() {
    int bemenet;
    char c;
    bool ervenyesBemenet = false;
    while (!ervenyesBemenet) {
        if (scanf("%d%c", &bemenet, &c) == 2 && (c == '\n' || c == ' ' || c == '\t')) {
            ervenyesBemenet = true;
        } else {
            printf("HIBA: Ervenytelen bemenet, kerem probalja ujra: ");
            while (getchar() != '\n');
        }
    }
    return bemenet;
}
/*
    Ez a fuggveny beolvas a felhasznalotol egy lebegöpontos szamot a standard bemenetrõl.
   Sikeres beolvasas eseten visszaadja a lebegöpontos szamot, egyebkent hibat jelez es ujra bekeri a bemenetet.
*/
double beolvasDouble(){
    double siker, bemenet;
    siker=scanf("%lf", &bemenet);
    while (siker != 1) {
        printf("\nHIBA: Ervenytelen bemenet, kerem probalja ujra.\n");
        scanf("%*[^\n]");
        siker = scanf("%lf", &bemenet);
    }
    return bemenet;
}




