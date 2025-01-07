/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** check_plane_arrival_coords
*/

#include <SFML/Graphics.h>
#include <stdbool.h>
#include <math.h>
#include "structure.h"
#include "entity.h"

bool plane_has_arrived(aircraft_t *aircraft)
{
    int x1 = (int)aircraft->takeoff_pos.x;
    int x2 = (int)aircraft->landing_pos.x;
    int y1 = (int)aircraft->takeoff_pos.y;
    int y2 = (int)aircraft->landing_pos.y;
    float distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    float travel_time = distance / aircraft->velocity;

    if (sfTime_asSeconds(sfClock_getElapsedTime(aircraft->position_clock))
        > travel_time)
        return true;
    return false;
}
