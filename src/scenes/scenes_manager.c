/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** scenes_manager
*/

#include <SFML/Graphics.h>
#include "scenes.h"
#include <stdio.h>

linked_list_t *load_scenes(engine_t *engine)
{
    linked_list_t *scenes_list = new_list();
    scene_t *main_page = init_main_page(engine);
    scene_t *settings_page = init_settings_page(engine);
    scene_t *game_scene = init_game_scene(engine);

    scenes_list = push_front_list(scenes_list, main_page);
    scenes_list = push_front_list(scenes_list, settings_page);
    scenes_list = push_front_list(scenes_list, game_scene);
    return scenes_list;
}
