// gcc -o ModeloIA ModeloIA.c

#include <sched.h>
#include <signal.h>
#include <stdio.h>  // file handling functions
#include <stdlib.h> // atoi
#include <string.h> // strtok
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>

#include "digiNet.h"

//**********************//
// Funciones auxiliares //
//**********************//

void limpiar() {
    printf("Presione Enter para continuar...\n");
    getchar();
    system("clear");
}

void print_matrix(double **mat, int nrows, int ncols, int offset_row, int offset_col) {
/*
 * Dada una matriz (mat), una cantidad de filas (nrows) y columnas (ncols) a
 * imprimir, y una cantidad de filas (offset_row) y columnas (offset_col) a
 * ignorar, imprime por salida estándar nrows x ncols de la matriz
 */
    for (int row = 0; row < nrows; row++) {
        for (int col = 0; col < ncols; col++) {
            printf("%f ", mat[row + offset_row][col + offset_col]);
        }
        printf("\n");
    }
}

void unload_data() {
/*
 * Liberar la memoria
 */
    free(digits);
    free(mat1);
    free(mat2);
    free(mat3);
    free(mat4);
    free(vec1);
    free(vec2);
    free(vec3);
    free(vec4);
    free(str);
    free(data);
    free(capa1);
    free(capa2);
    free(capa3);
    free(capa4);
}

void print(void *arg) { printf("Hola, soy %d\n", *(int *)arg); } 

void imprimir_imagen(double **data, double *predicciones, int posicion) {
    if (posicion < 0 || posicion >= data_nrows) {
        printf("Posición fuera de rango. Debe estar entre 0 y %d.\n", data_nrows - 1);
        return;
    }

    printf("Imagen en la posición %d:\n", posicion);
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            if (data[posicion][i * 28 + j] > 191) {
                printf("# ");
            } else if (data[posicion][i * 28 + j] > 127) {
                printf("$ ");
            } else if (data[posicion][i * 28 + j] > 63) {
                printf("O ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("El dígito real en la posición %d es: %f\n", posicion, digits[posicion]);
    printf("El dígito predicho en la posición %d es: %f\n", posicion, predicciones[posicion]);
}

//**************************//
// Cargar y descargar datos //
//**************************//

int read_matrix(double **mat, char *file, int nrows, int ncols, int fac) {
    
/*
 * Dada una matrix (mat), un nombre de fichero (file), una cantidad de filas
 * (nrows) y columnas (ncols), y un multiplicador (fac, no se usa, es 1), deja en mat la
 * matriz (de dimensión nrows x ncols) de datos contenida en el fichero con
 * nombre file
 */

    char *buffer = (char *)malloc(nrows * ncols * sizeof(char)); // Esto contendrá toda la fila
    char *record;
    FILE *fstream = fopen(file, "r");
    double aux;
    
    // Reservar memoria para las filas
    for (int i = 0; i < nrows; i++) {
        mat[i] = malloc(ncols * sizeof(double));
    }
    
    // Control de errores
    if (fstream == NULL) {
        printf("Error en read_matrix: %s\n", strerror(errno));
        free(buffer);
        return -1;
    }

    //printf("Archivo %s abierto correctamente\n", file);

    // Leer, separar, y reservar filas
    for (int row = 0; row < nrows; row++) {
        if (fgets(buffer, nrows*ncols, fstream) != NULL) {
            
            record = strtok(buffer, " ");
            
            // Leer, separar, y reservar columnas de la fila
            for (int column = 0; column < ncols; column++) {
                // printf("record: %s\n", record);
                if (record) {
                    // printf("Fila %d, columna %d: %s\n", row, column, record);
                    aux = strtod(record, NULL) * (float)fac;
                    mat[row][column] = aux;
                    record = strtok(NULL, " ");
                } else {
                    printf("Error en el file %s, fila %d, columna %d: %s\n", file, row, column, strerror(errno));
                    free(buffer);
                    return -1;
                }
                // Siguiente Token
            }
        } else {
            printf("Error al leer la fila %d del archivo: %s\n", row, strerror(errno));
            free(buffer);
            return -1;
        }
    }

    printf("Archivo %s leído correctamente\n", file);
    // Hay que cerrar ficheros y liberar memoria
    fclose(fstream);
    free(buffer);
    free(record);
    return 0;
}

int read_vector(double *vect, char *file, int nrows) {
/*
 * Dado un vector (vect), un nombre de fichero (file), y una cantidad de filas
 * (nrows), deja en vect el vector (de dimensión nrows) de datos contenido en
 * el fichero con nombre file
 */

    char *buffer = (char *)malloc(nrows * sizeof(char)); // Esto contendrá el valor
    double aux;
    FILE *fstream = fopen(file, "r");
    if (fstream == NULL) {
        printf("Error al abrir el archivo %s: %s\n", file, strerror(errno));
        free(buffer);
        return -1;
    }

    //printf("Archivo %s abierto correctamente\n", file);
    for (int row = 0; row < nrows; row++) {
        // leer el valor
        // printf("Fila %d\n", row);
        if (fgets(buffer, nrows+1, fstream) != NULL) {
            aux = strtod(buffer, NULL);
            if (aux == 0 && buffer[0] != '0') {
                printf("Error en la conversión de cadena a double en la fila %d: %s\n", row, strerror(errno));
                free(buffer);
                fclose(fstream);
                return -1;
            } else {
                // printf("Valor: %f\n", aux);
                vect[row] = aux;
            }
        } else {
            printf("Error al leer la fila %d del archivo: %s\n", row, strerror(errno));
            free(buffer);
            fclose(fstream);
            return -1;
        }
    
    }

    printf("Archivo %s leído correctamente\n", file);

    // Hay que cerrar ficheros y liberar memoria
    fclose(fstream);
    free(buffer);
    return 0;
}

void load_data(char *path) {
/*
 * Dado un directorio en el que están los datos y parámetros, los carga en las
 * variables de entorno  
 */

    printf("Cargando datos...\n");
    printf("------------------\n");

    str = malloc(100 * sizeof(char)); // Para los nombres de los ficheros
    
    digits = malloc(data_nrows * sizeof(double)); // Los valores que idealmente predeciremos
    sprintf(str, "%scsvs/digits.csv", path);
    read_vector(digits, str, data_nrows);
    //printf("Vector digits cargado\n");
    //printf("                         \n");
    
    data = malloc(data_nrows * sizeof(double));
    sprintf(str, "%scsvs/data.csv", path);
    read_matrix(data, str, data_nrows, data_ncols, 1);
    //printf("Matrix data cargada\n");
    //printf("------------------\n");

    // Las matrices
    mat1 = malloc(matrices_rows[0] * sizeof(double));
    sprintf(str, "%sparameters/weights%d_%d.csv", path, 0, seed);
    read_matrix(mat1, str, matrices_rows[0], matrices_columns[0], 1);
    //printf("Matrix 1 cargada\n");
    //printf("                         \n");

    mat2 = malloc(matrices_rows[1] * sizeof(double));
    sprintf(str, "%sparameters/weights%d_%d.csv", path, 1, seed);
    read_matrix(mat2, str, matrices_rows[1], matrices_columns[1], 1);
    //printf("Matrix 2 cargada\n");
    //printf("                         \n");

    mat3 = malloc(matrices_rows[2] * sizeof(double));
    sprintf(str, "%sparameters/weights%d_%d.csv", path, 2, seed);
    read_matrix(mat3, str, matrices_rows[2], matrices_columns[2], 1);
    //printf("Matrix 3 cargada\n");
    //printf("                         \n");

    mat4 = malloc(matrices_rows[3] * sizeof(double));
    sprintf(str, "%sparameters/weights%d_%d.csv", path, 3, seed);
    read_matrix(mat4, str, matrices_rows[3], matrices_columns[3], 1);
    //printf("Matrix 4 cargada\n");
    //printf("------------------\n");

    // Los vectores
    vec1 = malloc(vector_rows[0] * sizeof(double));
    sprintf(str, "%sparameters/biases%d_%d.csv", path, 0, seed);
    read_vector(vec1, str, vector_rows[0]);
    //printf("Vector 1 cargado\n");
    //printf("                         \n");

    vec2 = malloc(vector_rows[1] * sizeof(double));
    sprintf(str, "%sparameters/biases%d_%d.csv", path, 1, seed);
    read_vector(vec2, str, vector_rows[1]);
    //printf("Vector 2 cargado\n");
    //printf("                         \n");

    vec3 = malloc(vector_rows[2] * sizeof(double));
    sprintf(str, "%sparameters/biases%d_%d.csv", path, 2, seed);
    read_vector(vec3, str, vector_rows[2]);
    //printf("Vector 3 cargado\n");
    //printf("                         \n");

    vec4 = malloc(vector_rows[3] * sizeof(double));
    sprintf(str, "%sparameters/biases%d_%d.csv", path, 3, seed);
    read_vector(vec4, str, vector_rows[3]);
    //printf("Vector 4 cargado\n");
}

//******************************//
// Funciones de la red neuronal //
//******************************//

double** mat_mul(double **mat1, double **mat2, int nrows, int ncols, int n) {
    double **result = malloc(nrows * sizeof(*result));
    for (int i = 0; i < nrows; i++) {
        result[i] = malloc(ncols * sizeof(double));
    }

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

double** sum_vect(double **mat, double *vec, int nrows, int ncols) {
    double **result = malloc(nrows * sizeof(*result));
    for (int i = 0; i < nrows; i++) {
        result[i] = malloc(ncols * sizeof(double));
    }

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            result[i][j] = mat[i][j] + vec[j];
        }
    }
    return result;
}

double** relu(double **mat, int nrows, int ncols) {
    double **result = malloc(nrows * sizeof(*result));
    for (int i = 0; i < nrows; i++) {
        result[i] = malloc(ncols * sizeof(double));
    }

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (mat[i][j] < 0) {
                result[i][j] = 0;
            } else {
                result[i][j] = mat[i][j];
            }
        }
    }

    return result;
}

double* argmax(double **mat, int nrows, int ncols) {
    double *result = malloc(nrows * sizeof(double));
    for (int i = 0; i < nrows; i++) {
        int max_index = 0;
        for (int j = 1; j < ncols; j++) {
            if (mat[i][j] > mat[i][max_index]) {
                max_index = j;
            }
        }   
        result[i] = max_index;
    }
    return result;
}
