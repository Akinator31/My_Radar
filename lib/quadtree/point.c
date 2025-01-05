/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** point
*/

#include <stdlib.h>
#include "quadtree.h"

point_t *create_point(int x, int y, void *data)
{
    point_t *point = malloc(sizeof(point_t));

    point->x = x;
    point->y = y;
    point->data = data;
    return point;
}
