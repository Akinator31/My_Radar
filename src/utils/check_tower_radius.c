/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** check_tower_radius
*/

#include <math.h>
#include "structure.h"
#include "entity.h"

bool check_tower_radius(entity_t *aircraft_one_t,
    entity_t *aircraft_two_t, entity_t *tower_entity)
{
    aircraft_t *aircraft_one = ((aircraft_t *)(aircraft_one_t->data));
    aircraft_t *aircraft_two = ((aircraft_t *)(aircraft_two_t->data));

    return ((sqrt(pow((aircraft_one->position.x - (TOWER->pos.x + 37.5)), 2)
        + pow((aircraft_one->position.y - (TOWER->pos.y + 37.5)), 2))
        < TOWER->radius) || (sqrt(pow((aircraft_two->position.x -
        (TOWER->pos.x + 37.5)), 2) + pow((aircraft_two->position.y -
        (TOWER->pos.y + 37.5)), 2)) < TOWER->radius));
}
