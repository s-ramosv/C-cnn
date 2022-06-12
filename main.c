/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: GZPure <s.ramosv@udc.es>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/12 19:20:37 by GZPure        #+#    #+#                 */
/*   Updated: 2022/06/12 19:20:37 by GZPure        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
#include <stdlib.h>
#include "matrix.h"

int main() {
    double time_spent = 0.0;
    double time_spent1 = 0.0;
    int max_it = 100000;
    int it = 0;


    Matrix *matrix = create( 20, 20);
    random_fill(matrix, 0, 5);
    print_matrix(*matrix);

    for(it = 0; it <= max_it; it++) {

        clock_t begin = clock();

        //code to test 1
        Matrix *test0 = add_padding(*matrix, 3, 0);

        clock_t end = clock();

        destroy(test0);
        time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
    }

    for(it = 0; it <= max_it; it++) {

        clock_t begin = clock();

        //code to test 1
        Matrix *test1 = add_padding1(*matrix, 3, 0);

        clock_t end = clock();

        destroy(test1);
        time_spent1 += (double) (end - begin) / CLOCKS_PER_SEC;
    }

    destroy(matrix);
    printf("test 0: %f s \n", time_spent);
    printf("test 1: %f s \n", time_spent1);

    printf("test 0: %f%% of test 1\n", time_spent/time_spent1*100);

    printf("test 1: %.2f%% of test 0\n", time_spent1/time_spent*100);


    return 0;
}