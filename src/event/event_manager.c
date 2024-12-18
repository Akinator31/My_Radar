/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** event_manager
*/

#include <SFML/Graphics.h>
#include <stdbool.h>
#include "structure.h"

void analyse_event(engine_t *engine)
{
    if (engine->event.type == sfEvtClosed)
        sfRenderWindow_close(engine->window);
    if ((engine->event.type == sfEvtKeyPressed) &&
        sfKeyboard_isKeyPressed(sfKeyL)) {
        if (engine->show_hitbox)
            engine->show_hitbox = false;
        else
            engine->show_hitbox = true;
    }
    if ((engine->event.type == sfEvtKeyPressed) &&
        sfKeyboard_isKeyPressed(sfKeyS)) {
        if (engine->show_sprite)
            engine->show_sprite = false;
        else
            engine->show_sprite = true;
    }
}
