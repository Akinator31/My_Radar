/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** event_manager
*/

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "structure.h"

static void window_manager(engine_t *engine)
{
    if (engine->event.type == sfEvtClosed)
        sfRenderWindow_close(engine->window);
}

static void hitbox_visibility(engine_t *engine)
{
    if ((engine->event.type == sfEvtKeyPressed) &&
        sfKeyboard_isKeyPressed(sfKeyL)) {
        if (engine->show_hitbox)
            engine->show_hitbox = false;
        else
            engine->show_hitbox = true;
    }
}

static void sprite_visibility(engine_t *engine)
{
    if ((engine->event.type == sfEvtKeyPressed) &&
        sfKeyboard_isKeyPressed(sfKeyS)) {
        if (engine->show_sprite)
            engine->show_sprite = false;
        else
            engine->show_sprite = true;
    }
}

static void quadtree_visibility(engine_t *engine)
{
    if ((engine->event.type == sfEvtKeyPressed) &&
        sfKeyboard_isKeyPressed(sfKeyK)) {
        if (engine->show_quadtree) {
            engine->show_quadtree = false;
        } else {
            engine->show_quadtree = true;
        }
    }
}

void analyse_event(engine_t *engine)
{
    window_manager(engine);
    hitbox_visibility(engine);
    sprite_visibility(engine);
    quadtree_visibility(engine);
}
