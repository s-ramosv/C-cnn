/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cnns.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: GZPure <s.ramosv@udc.es>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/12 19:51:49 by GZPure        #+#    #+#                 */
/*   Updated: 2022/06/12 19:51:49 by GZPure        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

struct MatrixArray{
    Matrix matrix;
    struct MatrixArray *next;
};

