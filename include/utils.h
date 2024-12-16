/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** utils
*/

#ifndef INCLUDED_UTILS_H
    #define INCLUDED_UTILS_H
    #include <SFML/Graphics.h>
    #include "ressources.h"
    #include "structure.h"

sfRenderWindow *create_window(unsigned int width,
    unsigned int heigth, char *window_title);
void set_sprite_hover(sfSprite *sprite, engine_t *engine,
    sfTexture *new_texture, sfTexture *original_texture);
sfBool is_mouse_on_sprite(engine_t *engine,
    sfSprite *sprite);
scene_t *get_scene_by_id(engine_t *engine, int id);
int help(int ac, char **av);
sfVector2f get_random_pos(engine_t *engine);
ressource_t *get_ressource_by_id(linked_list_t *list, assets_t id);

#endif
