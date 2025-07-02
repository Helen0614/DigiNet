// gcc -o ModeloIA ModeloIA.c

#include "digiNet.h" 
#include <time.h>

double **data;
int data_nrows = 60000;
int data_ncols = 784;
char *my_path = "./";

int seed = 1;
int matrices_rows[4] = {784, 200, 100, 50};
int matrices_columns[4] = {200, 100, 50, 10};
int vector_rows[4] = {200, 100, 50, 10};
char *str;
int rows_per_div;

double *digits;
double *predicciones; 
double **mat1;
double **mat2;
double **mat3;
double **mat4;
double *vec1;
double *vec2;
double *vec3;
double *vec4;

double **capa1;
double **capa2;
double **capa3;
double **capa4;

int main(int argc, char *argv[]) {
/*
 * El programa recibe un único argumento, la cantidad de procesos que se
 * emplearán en la paralelización. Por ejemplo, parallel 3 tendrá que dividir
 * la matriz en tres, y lanzar tres procesos paralelos. Cada proceso, deberá
 * procesar un tercio de la matriz de datos
 */

    clock_t start, end;
    double cpu_time_used;  

     if (argc != 2) {
        printf("El programa debe tener un único argumento, la cantidad de procesos que se van a generar\n");
        exit(1);
    }
    
    system("clear");
    start = clock();
    load_data(my_path);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Datos cargados en %f segundos\n", cpu_time_used);
    printf("                 \n"); 
    limpiar();
    
    //*****//********//*****//
    //*****// FASE 1 //*****//
    //*****//********//*****//

    printf("Fase1:\n");

    // Imprimir las matrices cargadas
    printf("Matrix 1:\n");
    print_matrix(mat1, matrices_rows[0], matrices_columns[0], 0, 0);
    printf("-------------------------------------------------------\n");
    printf("Matriz 1 dibujada\n");
    limpiar();

    printf("Matrix 2:\n");
    print_matrix(mat2, matrices_rows[1], matrices_columns[1], 0, 0);
    printf("-------------------------------------------------------\n");
    printf("Matriz 2 dibujada\n");
    limpiar();

    printf("Matrix 3:\n");
    print_matrix(mat3, matrices_rows[2], matrices_columns[2], 0, 0);
    printf("-------------------------------------------------------\n");
    printf("Matriz 3 dibujada\n");
    limpiar(); 

    printf("Matrix 4:\n");
    print_matrix(mat4, matrices_rows[3], matrices_columns[3], 0, 0);
    printf("-------------------------------------------------------\n");
    printf("Matriz 4 dibujada\n");
    limpiar();

    //*****//********//*****//
    //*****// FASE 2 //*****//
    //*****//********//*****//

    printf("Fase 2:\n");

    //********//
    // Capa 1 //
    //********//

    capa1 = malloc(matrices_rows[0] * sizeof(*capa1));
    for (int i = 0; i < matrices_rows[0]; i++) {
        capa1[i] = malloc(matrices_columns[0] * sizeof(double));
    }

    // Capa 1 Multiplicación
    start = clock();
    capa1 = mat_mul(data, mat1, data_nrows, matrices_columns[0], matrices_rows[0]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matriz 1 multiplicada en %f segundos\n", cpu_time_used);

    // Capa 1 Suma
    start = clock();
    capa1 = sum_vect(capa1, vec1, data_nrows, matrices_columns[0]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Vector 1 sumado en %f segundos\n", cpu_time_used);

    // Capa 1 Relu
    start = clock();
    capa1 = relu(capa1, data_nrows, matrices_columns[0]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Relu 1 aplicado en %f segundos\n", cpu_time_used);

    printf("Capa 1 calculada\n");   
    printf("                 \n"); 

    //********//
    // Capa 2 //
    //********//

    capa2 = malloc(matrices_rows[1] * sizeof(*capa2));
    for (int i = 0; i < matrices_rows[1]; i++) {
        capa2[i] = malloc(matrices_columns[1] * sizeof(double));
    }

    // Capa 2 Multiplicación
    start = clock();
    capa2 = mat_mul(capa1, mat2, data_nrows, matrices_columns[1], matrices_rows[1]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matriz 2 multiplicada en %f segundos\n", cpu_time_used);

    // Capa 2 Suma
    start = clock();
    capa2 = sum_vect(capa2, vec2, data_nrows, matrices_columns[1]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Vector 2 sumado en %f segundos\n", cpu_time_used);

    // Capa 2 Relu
    start = clock();
    capa2 = relu(capa2, data_nrows, matrices_columns[1]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Relu 2 aplicado en %f segundos\n", cpu_time_used);

    printf("Capa 2 calculada\n");
    printf("                 \n"); 

    //********//
    // Capa 3 //
    //********//

    capa3 = malloc(matrices_rows[2] * sizeof(*capa3));
    for (int i = 0; i < matrices_rows[2]; i++) {
        capa3[i] = malloc(matrices_columns[2] * sizeof(double));
    }

    // Capa 3 Multiplicación
    start = clock();
    capa3 = mat_mul(capa2, mat3, data_nrows, matrices_columns[2], matrices_rows[2]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matriz 3 multiplicada en %f segundos\n", cpu_time_used);

    // Capa 3 Suma
    start = clock();
    capa3 = sum_vect(capa3, vec3, data_nrows, matrices_columns[2]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Vector 3 sumado en %f segundos\n", cpu_time_used);

    // Capa 3 Relu
    start = clock();
    capa3 = relu(capa3, data_nrows, matrices_columns[2]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Relu 3 aplicado en %f segundos\n", cpu_time_used);

    printf("Capa 3 calculada\n");
    printf("                 \n"); 

    //********//
    // Capa 4 //
    //********//

    capa4 = malloc(matrices_rows[3] * sizeof(*capa4));
    for (int i = 0; i < matrices_rows[3]; i++) {
        capa4[i] = malloc(matrices_columns[3] * sizeof(double));
    }

    // Capa 4 Multiplicación
    start = clock();
    capa4 = mat_mul(capa3, mat4, data_nrows, matrices_columns[3], matrices_rows[3]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matriz 4 multiplicada en %f segundos\n", cpu_time_used);

    // Capa 4 Suma
    start = clock();
    capa4 = sum_vect(capa4, vec4, data_nrows, matrices_columns[3]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Vector 4 sumado en %f segundos\n", cpu_time_used);

    // Capa 4 Relu
    start = clock();
    capa4 = relu(capa4, data_nrows, matrices_columns[3]);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Relu 4 aplicado en %f segundos\n", cpu_time_used);

    printf("Capa 4 calculada\n");

    //**************//
    // Predicciones //
    //**************//

    double *predicciones = argmax(capa4, data_nrows, matrices_columns[3]);  

    int aciertos = 0;
    for (int i = 0; i < data_nrows; i++) {
        if (predicciones[i] == digits[i]) {
            aciertos++;
        }
    }

    printf("                 \n");
    printf("Aciertos: %d\n", aciertos);
    printf("Porcentaje de aciertos: %f\n", ((float)aciertos / data_nrows) * 100);
    printf("                 \n"); 

    limpiar();

    int posicion;
    int continuar = 1;
    while (continuar) {
        printf("Ingrese una posición para ver la imagen y la predicción (o -1 para salir): ");
        scanf("%d", &posicion);
        if (posicion == -1) {
            continuar = 0;
        } else {
            imprimir_imagen(data, predicciones, posicion);
        }
    }

    unload_data();
    return 0;
}