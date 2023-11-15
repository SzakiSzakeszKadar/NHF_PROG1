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
   A felhasznalo valasztasatol fugguen vagy egy matrixot olvas be egy fajlbol,
   vagy a billentyuzetrol bekert ertekekkel hoz letre egyet.
*/
void file_vagy_billzet_1(Matrix **A) {
    printf("\n[1]\tA Bement_A.txt-bol szeretnem beolvasni az [A]  matrixot.\n");
    printf("[2]\tA felhasznalotol  szeretnem beolvasni az [A] matrix ertekeit.\n");
    printf("\nKerem valasszon egy menupontot:  ");
    int c1 = beolvasInt();
    switch (c1) {
        case 1:{
            *A = matrix_beolvas_file("bemenet_A.txt");
            if (*A != NULL) printf("\nRENDSZER: Az [A] matrix beolvasasara kerult.\n\n");
            else printf("\nHIBA: Az [A] matrix ervenytelen ertekeket tartalmaz.\n");
        break;
        }
        case 2:{
            printf("Az [A]  matrix beolvasasa. \n");
            *A = matrix_beolvas_billzet();
            printf("\n");
        break;
        }
        default:
            printf("\nÉrvenytelen bemenet, kerem probalja meg ujra megadni az erteket.\n");
        break;
    }
}
/*
    Az elobbi fuggveny, csak ket matrix eseten megirva.
*/
void file_vagy_billzet_2(Matrix **A,  Matrix **B){
    printf("\n[1]\tA Bement_A.txt-bol szeretnem beolvasni az [A]  matrixot.\n");
    printf("[2]\tA felhasznalotol  szeretnem beolvasni az [A] matrix ertekeit.\n");
    printf("\nKerem valasszon egy menupontot:  ");
    int c1;
    c1 = beolvasInt();
    switch(c1){
        case 1:{
            *A = matrix_beolvas_file("bemenet_A.txt");
            if (*A != NULL) printf("\nRENDSZER: Az [A] matrix beolvasasra kerult.\n");
            else printf("\n HIBA: Az bemenet_A.txt ervenytelen ertekeket tartalmaz.");
        break;
        }
        case 2:{
            printf("\nAz [A]  matrix beolvasasa. \n");
            *A = matrix_beolvas_billzet();
            printf("\n");
        break;
        }
        default:
            printf("\nHIBA: Érvenytelen bemenet, kerem probalja meg ujra megadni az erteket.\n");
        break;
    }
    printf("\n[1]\tA bemenet_B.txt-bol szeretnem beolvasni a [B]  matrixot.\n");
    printf("[2]\tA felhasznalotol  szeretnem beolvasni az [B] matrix ertekeit.\n");
    printf("\nKerem valasszon egy menupontot:  ");
    int c2;
    c2 = beolvasInt();
    switch(c2){
        case 1:{
            *B= matrix_beolvas_file("bemenet_B.txt");
            if (*B != NULL) printf("\nRENDSZER: A [B] matrix beolvasasra kerult.\n");
            else printf("\n HIBA: Az [A] matrix ervenytelen ertekeket tartalmaz.");
        break;
        }
        case 2:{
            printf("\nAz [B]  matrix beolvasasra. \n");
            *B = matrix_beolvas_billzet();
            printf("\n");
        break;
        }
        default:
            printf("\nHIBA: Érvenytelen bemenet, kerem probalja meg ojra megadni az erteket.\n");
        break;
    }
}
/*
    Ket matrix szorzatanak kiszamitasa es eredmenyenek kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void szorzat_menupont(){
    Matrix *A = NULL;
    Matrix *B = NULL;
    file_vagy_billzet_2(&A, &B);
    if (A != NULL && B != NULL) {
            Matrix* M = matrixok_szorzasa(A, B);
            if (M != NULL) {
                printf("\nRENDSZER: Az [A] es [B] matrixok szorzasa elvegzesre kerult, es a szorzat el lett mentve a kimenet_matrix.txt file-ba.\n");
                printf("\nAz eredmeny [M] matrix:\n\n");
                matrix_kiiratasa_konzol(M);
                matrix_kiiratasa_file(M, "kimenet_matrix.txt");
                matrix_felszabaditasa(M);
            }
            else  printf("\n HIBA: A szorzas nem lehetseges.\n");
    }
    else  printf("\n HIBA: A szorzas nem lehetseges, mert a jelzett bemenet file hibas ertekeket tartalmaz.\n");
    if (A != NULL) matrix_felszabaditasa(A);
    if (B != NULL) matrix_felszabaditasa(B);
}
/*
    Ket matrix  osszegenek kiszamitasa es eredmenyenek kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void osszeg_menupont(){
    Matrix *A = NULL;
    Matrix *B = NULL;
    file_vagy_billzet_2(&A, &B);
    if (A != NULL && B != NULL) {
            Matrix* M = matrixok_osszeadasa(A, B);
            if (M != NULL) {
                printf("\nRENDSZER: Az [A] es [B] matrixok osszeadasa elvegzesre kerult, es a szorzat el lett mentve a kimenet_matrix.txt file-ba.\n");
                printf("\nAz eredmeny [M] matrix:\n\n");
                matrix_kiiratasa_konzol(M);
                matrix_kiiratasa_file(M, "kimenet_matrix.txt");
                matrix_felszabaditasa(M);
            }
            else  printf("\n HIBA: Az osszeadas nem lehetseges.\n");
    }
    else  printf("\n HIBA: Az osszeadas nem lehetseges, mert a jelzett bemenet file hibas ertekeket tartalmaz.\n");
    if (A != NULL) matrix_felszabaditasa(A);
    if (B != NULL) matrix_felszabaditasa(B);
}
/*
    Ket matrix kulonbsegenek kiszamitasa es eredmenyenek kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void kivonas_menupont(){
    Matrix *A = NULL;
    Matrix *B = NULL;
    file_vagy_billzet_2(&A,&B);
    if (A != NULL && B != NULL) {
            Matrix* M = matrixok_kivonasa(A, B);
            if (M != NULL) {
                printf("\nRENDSZER: Az [A] matrixbol kivonasra kerult a [B] matrix es a kulonbseg el lett mentve a kimenet_matrix.txt file-ba.\n");
                printf("\nAz eredmeny [M] matrix:\n\n");
                matrix_kiiratasa_konzol(M);
                matrix_kiiratasa_file(M, "kimenet_matrix.txt");
                matrix_felszabaditasa(M);
            }
            else  printf("A kivonas nem lehetseges.\n");
    }
    else  printf("\n HIBA: A kivonas nem lehetseges, mert a jelzett bemenet file hibas ertekeket tartalmaz.\n");
    if (A != NULL) matrix_felszabaditasa(A);
    if (B != NULL) matrix_felszabaditasa(B);
}
/*
    Egy matrix transzponaltjanak kiszamitasa es az eredmeny kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void transzponalt_menupont(){
    Matrix* A = NULL;
    file_vagy_billzet_1(&A);
    if(A != NULL){
        Matrix * T = matrix_transzponalasa(A);
        printf("RENDSZER: A transzponalt mentesre kerult a kimenet_matrix.txt file-ba\n");
        printf("\nAz [A] matrix transzponaltja:\n\n");
        matrix_kiiratasa_konzol(T);
        matrix_kiiratasa_file(T, "kimenet_matrix.txt");
        matrix_felszabaditasa(A);
        matrix_felszabaditasa(T);
    }
    else printf("\n HIBA: A transzponalas nem vegrehajthato, mert a bemenet_A.txt  hibas ertekeket tartalmaz.\n");
}
/*
    Egy matrix nyomanak kiszamitasa es az eredmeny kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void nyom_menupont(){
    Matrix* A = NULL;
    file_vagy_billzet_1(&A);
    if(A != NULL){
        double trace = matrix_nyoma(A);
        printf("RENDSZER: A nyom mentesre kerult a kimenet_eredmeny.txt file-ba\n");
        double_eredmeny_kiiratasa_file(trace, "eredmeny_kimenet.txt");
        printf("\nAz [A] matrix nyoma : Tr[A] = %.2lf \n",trace);
        matrix_felszabaditasa(A);
    }
    else printf("\nHIBA: A nyom nem szamithato, mert a bemenet_A.txt  hibas ertekeket tartalmaz.\n");
}
/*
    Egy matrix rangjanak kiszamitasa es az eredmeny kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void matrix_rangja_menupont(){
    Matrix* A = NULL;
    file_vagy_billzet_1(&A);
    if(A != NULL){
        int rang = matrix_rangja(A);
        printf("RENDSZER: A rang mentesre kerult a kimenet_eredmeny.txt file-ba\n");
        int_eredmeny_kiiratasa_file(rang, "eredmeny_kimenet.txt");
        printf("\nAz [A] matrix rangja: rang[A] = %d\n", rang);
        matrix_felszabaditasa(A);
    }
    else printf("\nHIBA: A rang nem szamithato, mert a bemenet_A.txt  hibas ertekeket tartalmaz.\n");
}
/*
    Egy matrix inverzenek kiszamitasa es az eredmeny kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void matrix_inverze_menupont() {
    Matrix* A = NULL;
    Matrix* I = NULL;
    file_vagy_billzet_1(&A);
    if(A != NULL){
        if(A->sorok == A->oszlopok){
            I = inverz_matrix(A);
            printf("RENDSZER: Az inverz mentesre kerult a kimenet_matrix.txt file-ba\n");
            printf("\nAz [A] matrix inverze:\n\n");
            matrix_kiiratasa_konzol(I);
            matrix_kiiratasa_file(I, "kimenet_matrix.txt");
            matrix_felszabaditasa(I);
        }
        else printf("\nHIBA: A matrix nem negyzetes, Gauss Eliminacio nem kerul futtatasra \n");
        matrix_felszabaditasa(A);
    }
    else printf("\nHIBA: Az inverz meghatarozasa nem vegrehajthato, mert a bemenet_A.txt  hibas ertekeket tartalmaz.\n");
}
/*
    Egy matrixra a Gauss Eliminacio futtatasa es a matrix futtatas utani alakjanak kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void Gauss_Eliminacio_menupont() {
    Matrix* A = NULL;
    file_vagy_billzet_1(&A);
    if(A != NULL){
        if(A->sorok == A->oszlopok){
        Gauss_Eliminacio_det_rang(A);
        printf("\nRENDSZER: A felsoharomszog alak mentesre kerult a kimenet_matrix.txt file-ba\n");
        printf("\nAz [A] matrix felsoharomszog alakja:\n\n");
        matrix_kiiratasa_konzol(A);
        matrix_kiiratasa_file(A, "kimenet_matrix.txt");
        }
        else printf("\nHIBA: A matrix nem negyzetes, Gauss Eliminacio nem kerul futtatasra \n");
        matrix_felszabaditasa(A);
    }
    else printf("\nHIBA: A  Gauss Eliminacio  nem vegrehajthato, mert a bemenet_A.txt  hibas ertekeket tartalmaz.\n");
}
/*
        Egy matrixra a megfelelo Gauss Eliminacio futtatasa es ezzel, ha egyertelmu a megoldas a linearis egyenletrendszer megoldasa
*/
void egyenletrendszer_megoldasa_menupont() {
    Matrix* A = NULL;
    file_vagy_billzet_1(&A);
    if (A != NULL) {
        Matrix* S = matrix_masolasa(A);
        double det = determinans_szamitas(S);
        matrix_felszabaditasa(S);
        if (det == 0) {
            printf("HIBA: Nem egyertelmû az egyenletrendszer megoldasa.\n");
            matrix_felszabaditasa(A);
        }
        else {
            int n = A->sorok;
            double* szabadtagok = (double*)malloc(n * sizeof(double));
            if (szabadtagok == NULL) {
                printf("HIBA: Nem sikerult memoriat foglalni a szabadtagoknak.\n");
                matrix_felszabaditasa(A);
                return;
            }
            printf("Kerem adja meg a szabadtagokat:\n\n");
            for (int i = 0; i < n; i++) {
                printf("[%d] egyenlet szabadtagja = ", i+1);
                szabadtagok[i] = beolvasDouble();
            }
            double* megoldasok = (double*)malloc(n * sizeof(double));
            if (megoldasok == NULL) {
                printf("HIBA: Nem sikerult memoriat foglalni az eredmenyeknek.\n");
                free(szabadtagok);
                matrix_felszabaditasa(A);
                return;
            }
            Gauss_Megoldas(A, szabadtagok, megoldasok);
            printf("\nAz A egyutthato matrixu egyenletrendszer megoldasai:\n\n");
            for (int i = 0; i < n; i++) {
                printf("x[%d] = %lf\n", i+1, megoldasok[i]);
            }
            free(megoldasok);
            free(szabadtagok);
            matrix_felszabaditasa(A);
        }
    }
    else printf("HIBA: Az [A] matrix ervenytelen ertekeket tartalmaz.\n");
}

/*
    Egy matrix determinansanak kiszamitasa es az eredmeny kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void determinans_menupont(){
    Matrix* A = NULL;
    file_vagy_billzet_1(&A);
    if(A != NULL){
        double det = determinans_szamitas(A);
        printf("RENDSZER: A determinans mentesre kerult a kimenet_eredmeny.txt file-ba\n");
        double_eredmeny_kiiratasa_file(det, "eredmeny_kimenet.txt");
        printf("\nAz [A] matrix determinansa: det[A] = %.2lf\n", det);
        matrix_felszabaditasa(A);
    }
    else printf("\nHIBA: A determinans nem szamithato, mert a bemenet_A.txt  hibas ertekeket tartalmaz.\n");
}
/*
    Harom pont altal meghatarozott haromszog teruletenek kiszamitasa es az eredmeny kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void haromszog_terulete_menupont(){
    Matrix* A = harom_pont_matrix();
    double det = 0.0;
    Gauss_Eliminacio_det_rang(A);
    if(A != NULL) det = determinans_szamitas(A);
    if(det != 0){
        double terulet = abs(det)/2.0;
        printf("\nAz A, B es C pontok altal meghatarozott haromszog terulete: T = %.2lf \n", terulet);
        double_eredmeny_kiiratasa_file(terulet, "eredmeny_kimenet.txt");
    }
    else printf("\nHIBA: A harom pont nem alkot egy haromszoget\n");
    matrix_felszabaditasa(A);
}
/*
    Harom pont kollinearitasanak eldontese es az eredmeny kiiratasa,
    valamint a hasznalt memoriateruletek felszabaditasa.
*/
void harom_pont_kollinearis_menupont(){
    Matrix *A = harom_pont_matrix();
    double det = 0.0;
    Gauss_Eliminacio_det_rang(A);
    if(A != NULL) det = determinans_szamitas(A);
    if(det == 0)printf("\nAz A, B es C pontok kollinearisak (Egy egyenesen helyezkednek el)\n");
    else printf("\nAz A, B es C pontok NEM kollinearisak\n");
    matrix_felszabaditasa(A);
}






