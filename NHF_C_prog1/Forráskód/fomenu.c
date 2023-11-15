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
//Fömenü megvalósitása
void fomenu() {
    cim();
    int menupont;
    bool leall=true;

    while (leall) {
        menu();
        menupont = beolvasInt();
        switch (menupont) {
            case 1:
                osszeg_menupont();
                break;
            case 2:
                kivonas_menupont();
                break;
            case 3:
                szorzat_menupont();
                break;
            case 4:
                Gauss_Eliminacio_menupont();
                break;
            case 5:
                determinans_menupont();
                break;
            case 6:
                nyom_menupont();
                break;
            case 7:
                matrix_inverze_menupont();
                break;
            case 8:
                egyenletrendszer_megoldasa_menupont();
                break;
            case 9:
                transzponalt_menupont();
                break;
            case 10:
                matrix_rangja_menupont();
                break;
            case 11:
                haromszog_terulete_menupont();
                break;
            case 12:
                harom_pont_kollinearis_menupont();
                break;
            case 13:
                printf("\nViszontlatasra!\n");
                leall=false;
            break;
            default:
                printf("\n\nHIBA: Ervenytelen bemenet kerem probalja meg ujra.\n");
            break;
        }
    }
}
