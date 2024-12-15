/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** scenes
*/

#ifndef INCLUDED_SCENES_H
    #define INCLUDED_SCENES_H
    #include "my_list.h"
    #include "engine.h"

linked_list_t *load_scenes(engine_t *engine);
scene_t *init_main_page(engine_t *engine);
scene_t *init_settings_page(engine_t *engine);
scene_t *init_game_scene(engine_t *engine);

#endif
