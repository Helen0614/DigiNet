#define _GNU_SOURCE
#define stacksize 1048576

#include <stdio.h>  
#include <stdlib.h>  

// Declaraciones extern (no definen, solo declaran)
extern double **data;
extern int data_nrows;
extern int data_ncols;
extern char *my_path;

extern int seed;
extern int matrices_rows[4];
extern int matrices_columns[4];
extern int vector_rows[4];
extern char *str;
extern int rows_per_div;

extern double *digits;
extern double *predicciones; 
extern double **mat1;
extern double **mat2;
extern double **mat3;
extern double **mat4;
extern double *vec1;
extern double *vec2;
extern double *vec3;
extern double *vec4;

extern double **capa1;
extern double **capa2;
extern double **capa3;
extern double **capa4;

//**********************//
// Funciones auxiliares //
//**********************//

void limpiar();
void print_matrix(double **mat, int nrows, int ncols, int row_offset, int col_offset);
void unload_data();
void print(void *arg);
void imprimir_imagen(double **data, double *predicciones, int posicion);
void print_num();

//**************************//
// Cargar y descargar datos //
//**************************//

int read_matrix(double **mat, char *file, int nrows, int ncols, int fac);
int read_vector(double *vect, char *file, int nrows);
void load_data(char *path); 

//******************************//
// Funciones de la red neuronal //
//******************************//

double** mat_mul(double **mat1, double **mat2, int nrows, int ncols, int n);
double** sum_vect(double **mat, double *vec, int nrows, int ncols);
double** relu(double **mat, int nrows, int ncols);
double* argmax(double **mat, int nrows, int ncols);