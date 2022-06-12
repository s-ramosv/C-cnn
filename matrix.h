/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: GZPure <s.ramosv@udc.es>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 00:40:47 by GZPure        #+#    #+#                 */
/*   Updated: 2022/05/30 00:40:47 by GZPure        ########  odam.nl          */
/*                                                                            */
/* ************************************************************************** */

//
// Created by puregz on 30/05/2022.
//

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    float* data;
} Matrix;

Matrix* create(int rows, int cols);
Matrix* copy_matrix(Matrix matrix);
void destroy(Matrix *matrix);
void print_matrix(Matrix matrix);

void scalar_fill(Matrix *matrix, float scalar);
void random_fill(Matrix *matrix, int min, int max);
void random_bin_fill(Matrix *matrix);

void scalar_product(Matrix *matrix, float scalar);
void scalar_sum(Matrix *matrix, float scalar);
void put_data(Matrix *matrix, const float* data);
void transpose(Matrix *matrix);
void v_flip(Matrix *matrix);
void h_flip(Matrix *matrix);

Matrix* dot_product(Matrix m1, Matrix m2);
Matrix* section_matrix(Matrix  m1, int row, int column, int height, int width);
Matrix* add_row(Matrix m1, int pos, const float row[]);
Matrix* add_col(Matrix m1, int pos, const float column[]);
Matrix* matrix_multiplication(Matrix m1, Matrix m2);

float matrix_fold_sum(Matrix m1);
float matrix_fold_mul(Matrix m1);
float matrix_avg(Matrix m1);
float matrix_max(Matrix m1);
float filter_convolution(Matrix m1, Matrix m2);

Matrix* max_pool(Matrix m1, const int shape[2], int stride);
Matrix* avg_pool(Matrix m1, const int shape[2], int stride);

Matrix* add_padding(Matrix m1, int pad, float scalar);
Matrix* add_padding1(Matrix m1, int pad, float scalar);

Matrix* activation_ReLU(Matrix m1);

//todo
void print_matrix_to_file(Matrix matrix);
Matrix* replace_value(Matrix matrix, int x, int y, float new);


#endif //MATRIX_H
