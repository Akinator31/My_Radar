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
    scene_t *game_scene = init_game_scene(engine);

    scenes_list = push_front_list_all(scenes_list, 1, game_scene);
    return scenes_list;
}
