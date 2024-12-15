/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** event
*/

#ifndef INCLUDED_EVENT_H
    #define INCLUDED_EVENT_H
    #include <SFML/Graphics.h>

void analyse_event(sfRenderWindow *window, sfEvent *event);
void manage_music(engine_t *engine, entity_t *entity);
void manage_pause_game(engine_t *engine, entity_t *entity);
void manage_chicken_click(entity_t *entity, engine_t *engine, scene_t *scene);

#endif
