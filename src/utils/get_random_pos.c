/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** get_random_pos
*/

#include <stdlib.h>
#include "structure.h"
#include "engine.h"

sfVector2f get_random_pos(engine_t *engine)
{
    int width = sfRenderWindow_getSize(engine->window).x;
    int height = sfRenderWindow_getSize(engine->window).y;
    sfVector2f random_pos = {(rand() % width) + (rand() % 500),
        (rand() % height) + (rand() % 500)};

    return random_pos;
}
