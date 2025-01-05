/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** quadtree
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_list.h"
#include "quadtree.h"

quadtree_t *create_quadtree(rectangle_t *boundary,
    int capacity, int depth_capacity)
{
    quadtree_t *quadtree = (quadtree_t *)malloc(sizeof(quadtree_t));

    quadtree->boundary = boundary;
    quadtree->capacity = capacity;
    quadtree->devided = false;
    quadtree->points = NULL;
    quadtree->depth = 0;
    quadtree->depth_capacity = depth_capacity;
    quadtree->northwest = NULL;
    quadtree->northeast = NULL;
    quadtree->southwest = NULL;
    quadtree->southeast = NULL;
    return quadtree;
}

void subdivide(quadtree_t *quadtree)
{
    int x = quadtree->boundary->x;
    int y = quadtree->boundary->y;
    int w = quadtree->boundary->w / 2;
    int h = quadtree->boundary->h / 2;
    rectangle_t *northwest_rect = create_rectangle(x, y, w, h);
    rectangle_t *northeast_rect = create_rectangle(x + w, y, w, h);
    rectangle_t *southwest_rect = create_rectangle(x, y + h, w, h);
    rectangle_t *southeast_rect = create_rectangle(x + w, y + h, w, h);

    quadtree->northwest = create_quadtree(northwest_rect, quadtree->capacity,
        quadtree->depth_capacity);
    quadtree->northeast = create_quadtree(northeast_rect, quadtree->capacity,
        quadtree->depth_capacity);
    quadtree->southwest = create_quadtree(southwest_rect, quadtree->capacity,
        quadtree->depth_capacity);
    quadtree->southeast = create_quadtree(southeast_rect, quadtree->capacity,
        quadtree->depth_capacity);
}

static void redistribute_elements(quadtree_t **quadtree, linked_list_t **temp)
{
    point_t *existing_point = NULL;

    while (*temp != NULL) {
        existing_point = ((point_t *)((*temp)->data));
        if (insert_element((*quadtree)->northwest, existing_point) ||
            insert_element((*quadtree)->northeast, existing_point) ||
            insert_element((*quadtree)->southwest, existing_point) ||
            insert_element((*quadtree)->southeast, existing_point)) {
            *temp = delete_node(&(*quadtree)->points, *temp);
        } else {
            *temp = (*temp)->next;
        }
    }
}

static bool subdivide_manager(quadtree_t **quadtree, point_t *point)
{
    linked_list_t *temp = (*quadtree)->points;

    if (!(*quadtree)->devided) {
        if ((*quadtree)->depth < (*quadtree)->depth_capacity) {
            subdivide(*quadtree);
            (*quadtree)->northwest->depth = (*quadtree)->depth + 1;
            (*quadtree)->northeast->depth = (*quadtree)->depth + 1;
            (*quadtree)->southwest->depth = (*quadtree)->depth + 1;
            (*quadtree)->southeast->depth = (*quadtree)->depth + 1;
            (*quadtree)->devided = true;
            return false;
        } else {
            (*quadtree)->points = push_front_list((*quadtree)->points, point);
            return true;
        }
        redistribute_elements(quadtree, &temp);
    }
    return false;
}

bool insert_element(quadtree_t *quadtree, point_t *point)
{
    if (!contains_point(quadtree->boundary, point))
        return false;
    if ((get_linked_list_len(quadtree->points) < quadtree->capacity)
        && !quadtree->devided) {
        quadtree->points = push_front_list(quadtree->points, point);
        return true;
    } else {
        if (subdivide_manager(&quadtree, point))
            return true;
        if (insert_element(quadtree->northwest, point))
            return true;
        if (insert_element(quadtree->northeast, point))
            return true;
        if (insert_element(quadtree->southwest, point))
            return true;
        if (insert_element(quadtree->southeast, point))
            return true;
        return false;
    }
}

static void manage_founded_elements(linked_list_t *temp, rectangle_t *range,
    linked_list_t **found, int *count)
{
    if (contains_point(range, ((point_t *)(temp->data)))) {
        *count += 1;
        *found = push_front_list(*found, ((point_t *)(temp->data)));
    }
}

linked_list_t *lauch_query(quadtree_t *quadtree, rectangle_t *range,
    linked_list_t *found, int *count)
{
    linked_list_t *temp = quadtree->points;

    if (!intersects_rectangle(quadtree->boundary, range)) {
        return found;
    } else {
        while (temp != NULL) {
            manage_founded_elements(temp, range, &found, count);
            temp = temp->next;
        }
        if (quadtree->devided) {
            lauch_query(quadtree->northwest, range, found, count);
            lauch_query(quadtree->northeast, range, found, count);
            lauch_query(quadtree->southwest, range, found, count);
            lauch_query(quadtree->southeast, range, found, count);
        }
        return found;
    }
}

void destroy_quadtree(quadtree_t *quadtree)
{
    if (quadtree == NULL)
        return;
    destroy_quadtree(quadtree->northwest);
    destroy_quadtree(quadtree->northeast);
    destroy_quadtree(quadtree->southwest);
    destroy_quadtree(quadtree->southeast);
    clear_list(quadtree->points);
    free(quadtree->boundary);
    free(quadtree);
}
