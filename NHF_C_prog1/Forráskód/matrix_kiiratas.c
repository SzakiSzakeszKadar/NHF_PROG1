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
   Fuggveny ami kiir egy matrixot a konzolra.
*/
void matrix_kiiratasa_konzol(Matrix* matrix) {
    if (matrix == NULL) printf("\nHIBA: A matrix ervenytelen.\n");
    for (int i = 0; i < matrix->sorok; i++) {
        for (int j = 0; j < matrix->oszlopok; j++) {
            printf("%.2f\t", matrix->adat[i][j]);
        }
        printf("\n");
    }
}
/*
   Fuggveny ami kiir egy matrixot file-ba
*/
void matrix_kiiratasa_file(Matrix* matrix, const char* filename){
    FILE *file = fopen(filename,"w");
    if(file == NULL) printf("\nHIBA: A fajl nem talalhato, vagy nem modosithato.\n");
    for (int i = 0; i < matrix->sorok; i++) {
        for (int j = 0; j < matrix->oszlopok; j++) {
            fprintf(file,"%.2f\t", matrix->adat[i][j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}
/*
   Fuggveny ami kiir egy lebegoponto eredmenyt file-ba
*/
void double_eredmeny_kiiratasa_file(double eredmeny, const char* filename){
    FILE *file = fopen(filename,"w");
    if(file == NULL) printf("\nHIBA: A fajl nem talalhato, vagy nem modosithato.\n");
    fprintf(file,"%.2f\t", eredmeny);
    fclose(file);
}
/*
   Fuggveny ami kiir egy egesz eredmenyt file-ba
*/
void int_eredmeny_kiiratasa_file(int eredmeny, const char* filename){
    FILE *file = fopen(filename,"w");
    if(file == NULL) printf("\nHIBA: A fajl nem talalhato, vagy nem modosithato.\n");
    fprintf(file,"%d\t", eredmeny);
    fclose(file);
}
/*
    Cim design elem megjelenitese
*/
void cim(){
    printf("     O   O  OOOOO  OOOOO  OOOO    OOO   O   O\n");
    printf("     OO OO  O   O    O    O   O    O     O O\n");
    printf("     O O O  OOOOO    O    OOOO     O      O\n");
    printf("     O   O  O   O    O    O  O     O     O O\n");
    printf("     O   O  O   O    O    O   O   OOO   O   O\n");
}
/*
    Menu szovegenek megjelenitese
*/
void menu(){
    printf("\n************* Matrix Fuggvenykonyvtar *************\n\n");
    printf("[1]\tKet NxM-es matrix osszegenek kiszamitasa\t \n");
    printf("[2]\tKet NxM-es matrix kulonbsegenek kiszamitasa\n");
    printf("[3]\tKet NxM-es matrix szorzatanak kiszamitasa\n");
    printf("[4]\tGauss eliminacio futtatasa NxN-es matrixra\n");
    printf("[5]\tNxN-es matrix determinansanak kiszamitasa\n");
    printf("[6]\tNxN-es matrix nyomanak (trace) kiszamitasa\n");
    printf("[7]\tNxN-es matrix inverzenek kiszamitasa\n");
    printf("[8]\tNxN-es egyutthatomatrixu egyertelmu linearis egyenletrendszer megoldasa\n");
    printf("[9]\tNxM-es matrix transzponaltjanak kiszamitasa\n");
    printf("[10]\tNxN-es matrix rangjanak kiszamitasa\n");
    printf("[11]\tEgy haromszog teruletenek meghatarozasa 3x3-as\n\tdeterminans segitsegevel\n");
    printf("[12]\tHarom sikbeli pont kollinearitasanak meghatarozasa 3x3-as\n\tdeterminans segitsegevel\n");
    printf("\n[13]\t Kilepes\n");
    printf("\nKerem valasszon egy menupontot: ");
}

