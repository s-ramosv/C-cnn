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

//todo
void print_matrix_to_file(Matrix matrix);
Matrix* add_row(Matrix matrix, int pos, const float* row);
Matrix* add_col(Matrix matrix, int pos, const float* col);
Matrix* replace_value(Matrix matrix, int x, int y, float new);


#endif //MATRIX_H
