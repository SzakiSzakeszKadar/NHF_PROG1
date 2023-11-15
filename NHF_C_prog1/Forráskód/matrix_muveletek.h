#ifndef MATRIX_MUVELETEK_H
#define MATRIX_MUVELETEK_H
Matrix* matrix_masolasa(Matrix* eredeti);
Matrix* matrixok_osszeadasa(Matrix* a, Matrix* b);
Matrix* matrixok_kivonasa(Matrix* a, Matrix* b);
Matrix* matrixok_szorzasa(Matrix* a, Matrix* b);
Matrix* matrix_transzponalasa(Matrix* a);
Matrix* inverz_matrix(Matrix* a);
void Gauss_Eliminacio_det_rang(Matrix* a);
void Gauss_Eliminacio_inverz(Matrix* a, Matrix* i);
void Gauss_Megoldas(Matrix* a, double* b, double* x);
void sorok_kivonasa(Matrix* matrix, int cel_sor, int forras_sor, double factor);
void sorok_osztasa(Matrix* matrix, int sor, double oszto);
void sorok_csereje(Matrix* matrix, int sor1, int sor2);
double matrix_nyoma(Matrix* a);
double determinans_szamitas(Matrix* a);
int matrix_rangja(Matrix* a);
#endif

