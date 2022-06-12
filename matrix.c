/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: GZPure <s.ramosv@udc.es>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 00:34:17 by GZPure        #+#    #+#                 */
/*   Updated: 2022/05/30 00:34:17 by GZPure        ######## odam.nl           */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
#include <stdlib.h>
#include <math.h>

#define SEED 10

#include "matrix.h"

Matrix* create(int rows, int cols){
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = malloc(cols * rows * sizeof(float));
    return matrix;
}

Matrix* copy_matrix(Matrix matrix){
    Matrix *m1 = malloc(sizeof(Matrix));
    m1->rows = matrix.rows;
    m1->cols = matrix.cols;
    m1->data = malloc(matrix.rows * matrix.cols * sizeof(float));
    for(int i = 0; i<matrix.rows*matrix.cols; i++)
        m1->data[i] = matrix.data[i];
    return m1;
}

void destroy(Matrix *matrix){
    free(matrix->data);
    free(matrix);
}

void print_matrix(Matrix matrix){
    int cols = matrix.cols;
    int rows = matrix.rows;

    printf("size: %d %d \n", rows, cols);

    for(int i = 0; i < cols*rows; i++){
        printf("%.4f ", matrix.data[i]);
        if(!((i+1)%cols)) printf("\n");
    }
    printf("\n");
}


// float array to array
void random_fill(Matrix *matrix, int min, int max){
    unsigned int seed = SEED;
    srand(seed);
    int i;
    for (i = 0; i < matrix->cols * matrix->rows; i++) {
        matrix->data[i] = (float)rand()/(float) RAND_MAX * (max-min) + min;
    }
}

void scalar_fill(Matrix *matrix, float scalar){
    unsigned int seed = SEED;
    srand(seed);

    for (int i = 0; i < matrix->cols * matrix->rows; i++)
        matrix->data[i] = scalar;
}

void random_bin_fill(Matrix *matrix){
    unsigned int seed = SEED;
    srand(seed);
    int i;
    for (i = 0; i < matrix->cols * matrix->rows; i++) {
        float random = (float) rand()/RAND_MAX < 0.5 ? 0 : 1;
        matrix->data[i] = random;
    }
}

void scalar_product(Matrix *matrix, float scalar){
    unsigned int seed = SEED;
    srand(seed);
    int i;
    for (i = 0; i < matrix->cols * matrix->rows; i++)
        matrix->data[i] = matrix->data[i] * scalar;
}

void scalar_sum(Matrix *matrix, float scalar){
    for (int i = 0; i < matrix->cols * matrix->rows; i++) {
        matrix->data[i] = matrix->data[i] + scalar;
    }
}

void put_data(Matrix *matrix, const float* data){
    for(int  i = 0; i < matrix->rows*matrix->cols; i++){
        matrix->data[i] = data[i];
    }
}

// 0 1 2  3 4 5  6 7 8
// 0 3 6  1 4 7  2 5 8
void transpose(Matrix *matrix){

    int rows = matrix->rows;
    int cols = matrix->cols;
    float* newdata = malloc(cols * rows * sizeof(float));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            newdata[j*rows + i] = matrix->data[i*cols + j];

    matrix->cols = rows;
    matrix->rows = cols;
    free(matrix->data);
    matrix->data = newdata;
}

// 0 1  2 3  4 5
// 4 5  2 3  0 1
void v_flip(Matrix *matrix){

    int rows = matrix->rows;
    int cols = matrix->cols;

    int new = cols*rows - cols;
    int off = 0;
    float* newdata = malloc(cols * rows * sizeof(float));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            newdata[new] = matrix->data[off];
            new++;
            off++;
        }
        new -= cols*2;
    }

    free(matrix->data);
    matrix->data = newdata;
}

// 0 1  2 3  4 5
// 1 0  3 2  5 4
void h_flip(Matrix *matrix){

    int rows = matrix->rows;
    int cols = matrix->cols;
    int off = 0;
    int new = cols-1;
    float* newdata = malloc(cols * rows * sizeof(float));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            newdata[new] = matrix->data[off];
            off++;
            new--;
        }
        new += cols*2;
    }

    free(matrix->data);
    matrix->data = newdata;
}

// dot_product(m1,m2) != dot_product(m2,m1)
Matrix* dot_product(Matrix m1, Matrix m2){

    int rows1 = m1.rows;
    int cols1 = m1.cols;

    int rows2 = m2.rows;
    int cols2 = m2.cols;

    if(cols1 != rows2) return NULL;

    int common = rows2;
    float acc = 0;

    float* newdata = malloc(rows1 * cols2 * sizeof(float));

    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols2; j++){
            for(int k = 0; k < common; k++){
                acc += m1.data[i*common + k] * m2.data[k*cols2 + j];
            }
            newdata[i*(common+1) + j] = acc;
            acc = 0;
        }
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows1;
    matrix->cols = cols2;
    matrix->data = newdata;
    return matrix;
}

Matrix* section_matrix(Matrix  m1, int row, int column, int height, int width){
    float* newdata = malloc(width * height * sizeof(float));

    int new = 0;
    int old = row * m1.cols + column;

    int h = (height + row) < m1.rows ? height : m1.rows - row;
    int w = (width + column) < m1.cols ? width : m1.cols - column;

    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            newdata[new] = m1.data[old];
            old++;
            new++;
        }
        old += (m1.cols - w);
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = h;
    matrix->cols = w;
    matrix->data = newdata;
    return matrix;
}

Matrix* add_row(Matrix m1, int pos, const float row[]){

    pos = pos > m1.rows ? m1.rows : pos;
    pos = pos < 0 ? 0 : pos;

    int rows = m1.rows + 1;
    int cols = m1.cols;
    int i, j;

    float* newdata = malloc(rows * cols * sizeof(float));

    // first elements of m1
    for(i = 0; i < pos*cols; i++){
        newdata[i] = m1.data[i];
    }
    // added row row[]
    for(j = 0; j < cols; j++, i++){
        newdata[i] = row[j];
    }
    for(; i < rows*cols; i++){
        newdata[i] = m1.data[i-cols];
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

Matrix* add_col(Matrix m1, int pos, const float column[]){

    pos = pos > m1.cols ? m1.cols : pos;
    pos = pos < 0 ? 0 : pos;

    int rows = m1.rows;
    int cols = m1.cols + 1;
    int i, j, k = 0;

    float* newdata = malloc(rows * cols * sizeof(float));

    // first elements of m1

    for(i = 0; i < pos; i++){
        for(j = 0; j < rows; j++){
            newdata[j*cols + i] = m1.data[j*(cols - 1) + i];
        }
    }

    // added row
    for(k = 0; k < rows; k++){
        newdata[k*cols + pos] = column[k];
    }

    // remaining m1 data
    for(i++; i < cols; i++){
        for(j = 0; j < rows; j++){
            newdata[j*cols + i] = m1.data[j*(cols - 1) + i - 1];
        }
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

// filter convolution layers
Matrix* matrix_multiplication(Matrix m1, Matrix m2) {

    // if(m1.rows != m2.rows || m1.cols != m2.cols) exit(-1);

    int rows = m1.rows < m2.rows ? m1.rows : m2.rows;
    int cols = m1.cols < m2.cols ? m1.cols : m2.cols;

    float* newdata = malloc(rows * cols * sizeof(float));

    for(int i = 0; i < rows*cols; i++)
        newdata[i] = m1.data[i] * m2.data[i];

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

float matrix_fold_sum(Matrix m1) {

    // if(m1.rows != m2.rows || m1.cols != m2.cols) exit(-1);

    int rows = m1.rows;
    int cols = m1.cols;

    float acc = 0;

    for(int i = 0; i < rows*cols; i++)
        acc += m1.data[i];
    return acc;
}

float matrix_fold_mul(Matrix m1) {

    // if(m1.rows != m2.rows || m1.cols != m2.cols) exit(-1);

    int rows = m1.rows;
    int cols = m1.cols;

    float acc = 0;

    for(int i = 0; i < rows*cols; i++)
        acc *= m1.data[i];
    return acc;
}

float matrix_avg(Matrix m1) {

    // if(m1.rows != m2.rows || m1.cols != m2.cols) exit(-1);

    int rows = m1.rows;
    int cols = m1.cols;

    float acc = 0;

    for(int i = 0; i < rows*cols; i++)
        acc += m1.data[i];
    return  acc / (float)(rows*cols);
}

float matrix_max(Matrix m1) {

    float max = m1.data[0];

    for(int i = 1; i < m1.rows*m1.cols; i++)
        max = m1.data[i] > max ? m1.data[i] : max;
    return  max;
}

float filter_convolution(Matrix m1, Matrix m2) {

    // if(m1.rows != m2.rows || m1.cols != m2.cols) exit(-1);

    int rows = m1.rows < m2.rows ? m1.rows : m2.rows;
    int cols = m1.cols < m2.cols ? m1.cols : m2.cols;

    float acc = 0;

    for(int i = 0; i < rows*cols; i++)
        acc += m1.data[i] * m2.data[i];
    return acc;
}

Matrix* filter(Matrix m1, Matrix filter, int stride) {

    // only works when x = y
    int cols_filter = filter.cols;
    int rows_filter = filter.rows;

    int cols_m1 = m1.cols;
    int rows_m1 = m1.rows;

    int rows = (int) (((float) cols_m1/(float) stride) + 0.5);
    int cols = (int) (((float) rows_m1/(float) stride) + 0.5);

    float* newdata = malloc(rows * cols * sizeof(float));

    int new = 0;

    for(int i = 0; i < rows_m1; i += stride) {
        for(int j = 0; j < cols_m1; j += stride) {
            Matrix *section = section_matrix(m1, i, j, cols_filter, rows_filter);
            newdata[new++] = filter_convolution(*section, filter);
            destroy(section);
        }
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

// pooling layers
Matrix* max_pool(Matrix m1, const int shape[2], int stride) {

    // if(m1.rows != m2.rows || m1.cols != m2.cols) exit(-1);

    // only works when x = y
    int pool_x = shape[0];
    int pool_y = shape[1];

    int cols_m1 = m1.cols;
    int rows_m1 = m1.rows;

    int rows = (int) (((float) cols_m1/(float) stride) + 0.5);
    int cols = (int) (((float) rows_m1/(float) stride) + 0.5);

    //int rows = (int) round((float) cols_m1 / (float) stride);
    //int cols = (int) round((float) rows_m1 / (float) stride);

    float* newdata = malloc(rows * cols * sizeof(float));

    int new = 0;

    for(int i = 0; i < rows_m1; i += stride) {
        for(int j = 0; j < cols_m1; j += stride) {
            Matrix *section = section_matrix(m1, i, j, pool_x, pool_y);
            newdata[new++] = matrix_max(*section);
            destroy(section);
        }
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

Matrix* avg_pool(Matrix m1, const int shape[2], int stride) {

    // if(m1.rows != m2.rows || m1.cols != m2.cols) exit(-1);

    // only works when x = y
    int pool_x = shape[0];
    int pool_y = shape[1];

    int cols_m1 = m1.cols;
    int rows_m1 = m1.rows;

    int rows = (int) (((float) cols_m1/(float) stride) + 0.5);
    int cols = (int) (((float) rows_m1/(float) stride) + 0.5);

    //int rows = (int) round((float) cols_m1 / (float) stride);
    //int cols = (int) round((float) rows_m1 / (float) stride);

    float* newdata = malloc(rows * cols * sizeof(float));

    int new = 0;

    for(int i = 0; i < rows_m1; i += stride) {
        for(int j = 0; j < cols_m1; j += stride) {
            Matrix *section = section_matrix(m1, i, j, pool_x, pool_y);
            newdata[new++] = matrix_avg(*section);
            destroy(section);
        }
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

// 5% faster with bigger values
Matrix* add_padding(Matrix m1, int pad, float scalar){

    int padding = pad > 0 ? pad : 1 ;

    int rows = m1.rows + 2*padding;
    int cols = m1.cols + 2*padding;

    float* newdata = malloc(rows * cols * sizeof(float));
    int new = 0, old = 0;

    for(; new < cols*padding; new++){
        newdata[new] = scalar;
    }

    for(; old < m1.cols*m1.rows;){
        for(int p = 0; p < padding; p++){
            newdata[new] = scalar;
            new++;
        }
        for(int p = 0; p < m1.cols; p++){
            newdata[new] = m1.data[old];
            new++;
            old++;
        }
        for(int p = 0; p < padding; p++){
            newdata[new] = scalar;
            new++;
        }
    }

    for(; new < cols*rows; new++){
        newdata[new] = scalar;
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

// 10-12% better with smaller than 50*50 matrixes
Matrix* add_padding1(Matrix m1, int pad, float scalar){

    int padding = pad > 0 ? pad : 1 ;

    int rows = m1.rows + 2*padding;
    int cols = m1.cols + 2*padding;

    float* newdata = malloc(rows * cols * sizeof(float));
    int new = 0, old = 0;

    for(int end = cols*rows - 1; new < cols*padding; new++, end--){
        newdata[new] = scalar;
        newdata[end] = scalar;
    }

    for(; old < m1.cols*m1.rows;){
        for(int p = 0; p < padding; p++){
            newdata[new] = scalar;
            new++;
        }
        for(int p = 0; p < m1.cols; p++){
            newdata[new] = m1.data[old];
            new++;
            old++;
        }
        for(int p = 0; p < padding; p++){
            newdata[new] = scalar;
            new++;
        }
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}

Matrix* activation_ReLU(Matrix m1){

    int rows = m1.rows;
    int cols = m1.cols;

    float* newdata = malloc(rows * cols * sizeof(float));
    int i = 0;

    for(; i < cols*rows; i++){
        newdata[i] = m1.data[i] > 0 ? m1.data[i] : 0;
    }

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = newdata;
    return matrix;
}
