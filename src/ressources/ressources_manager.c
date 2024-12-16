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
#include "ressources.h"

static const char *assets[] = {
    "./assets/images/game_scene/world_map.png"
};

linked_list_t *destroy_ressources(linked_list_t *ressources_list)
{
    linked_list_t *temp = ressources_list;

    while (temp != NULL)
    {
        if (((ressource_t *)(temp->data))->type == TEXTURE) {
            sfTexture_destroy((sfTexture *)((ressource_t *)
                (temp->data))->ressource);
            free(temp->data);
        }
        temp = temp->next;
    }
    return ressources_list;
}

ressource_t *create_ressources(const char *filepath, ressource_type_t type, assets_t id)
{
    ressource_t *ressource = malloc(sizeof(ressource_t));
    sfTexture *texture = NULL;

    if (type == TEXTURE) {
        texture = sfTexture_createFromFile(filepath, NULL);
        ressource->id = id;
        ressource->ressource = texture;
        ressource->type = type;
    }
    return ressource;
}

linked_list_t *get_ressources_list(void)
{
    linked_list_t *ressources_list = new_list();

    ressources_list = push_front_list(ressources_list,
        create_ressources(assets[0], TEXTURE, BACKGROUND));
    return ressources_list;
}
