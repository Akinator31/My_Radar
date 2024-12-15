/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** ressources_manager
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my_radar.h"
#include "structure.h"

static const char *assets[] = {
    "assets/images/game_scene/world_map.png"
};

linked_list_t *destroy_ressources(linked_list_t *ressources_list)
{
    sfTexture_destroy(ressources->background);
}

linked_list_t *create_ressources(void)
{
    linked_list_t *ressources_list = new_list();

    ressources_list = push_front_list(ressources_list,
        sfTexture_createFromFile(assets[0], NULL));
    return ressources_list;
}
