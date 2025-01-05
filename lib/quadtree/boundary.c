/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** boundary
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "quadtree.h"

rectangle_t *create_rectangle(int x, int y, int w, int h)
{
    rectangle_t *boundary = (rectangle_t *)malloc(sizeof(rectangle_t));

    boundary->x = x;
    boundary->y = y;
    boundary->w = w;
    boundary->h = h;
    return boundary;
}

bool contains_point(rectangle_t *rectangle, point_t *point)
{
    return (point->x >= rectangle->x &&
            point->x <= rectangle->x + rectangle->w &&
            point->y >= rectangle->y &&
            point->y <= rectangle->y + rectangle->h);
}

bool intersects_rectangle(rectangle_t *first, rectangle_t *second)
{
    return !((second->x - second->w > first->x + first->w) ||
        (second->x + second->w < first->x - first->w) ||
        (second->y - second->h > first->y + first->h) ||
        (second->y + second->h < first->y - first->h));
}
