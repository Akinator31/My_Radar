/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** quadtree
*/

#ifndef INCLUDED_QUADTREE_H
    #define INCLUDED_QUADTREE_H
    #include <stdbool.h>
    #include "my_list.h"

typedef struct point_s point_t;
typedef struct rectangle_s rectangle_t;
typedef struct quadtree_s quadtree_t;

struct point_s {
    int x;
    int y;
    void *data;
};

struct rectangle_s {
    int x;
    int y;
    int w;
    int h;
};

struct quadtree_s {
    rectangle_t *boundary;
    linked_list_t *points;
    int capacity;
    bool devided;
    int depth;
    int depth_capacity;
    quadtree_t *northwest;
    quadtree_t *northeast;
    quadtree_t *southwest;
    quadtree_t *southeast;
};

quadtree_t *create_quadtree(rectangle_t *boundary,
    int capacity, int depth_capacity);
rectangle_t *create_rectangle(int x, int y, int w, int h);
point_t *create_point(int x, int y, void *data);
void subdivide(quadtree_t *quadtree);
bool insert_element(quadtree_t *quadtree, point_t *point);
bool contains_point(rectangle_t *rectangle, point_t *point);
bool intersects_rectangle(rectangle_t *first, rectangle_t *second);
linked_list_t *lauch_query(quadtree_t *quadtree, rectangle_t *range,
    linked_list_t *found, int *count);
void destroy_quadtree(quadtree_t *quadtree);

#endif
