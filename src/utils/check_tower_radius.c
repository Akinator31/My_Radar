/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** check_tower_radius
*/

#include <math.h>
#include "structure.h"
#include "entity.h"

static float calculate_distance(sfVector2f pos1, sfVector2f pos2)
{
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

bool check_tower_radius(entity_t *aircraft_one_t, entity_t *aircraft_two_t,
    entity_t *tower_entity)
{
    aircraft_t *aircraft_one = (aircraft_t *)(aircraft_one_t->data);
    aircraft_t *aircraft_two = (aircraft_t *)(aircraft_two_t->data);
    sfVector2f tower_center = {
        TOWER->pos.x + 75 / 2,
        TOWER->pos.y + 75 / 2
    };

    return (calculate_distance(aircraft_one->position, tower_center)
        < TOWER->radius || calculate_distance(aircraft_two->position,
        tower_center) < TOWER->radius);
}
