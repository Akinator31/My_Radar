/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** ressources
*/

#ifndef INCLUDED_RESSOURCES_H
    #define INCLUDED_RESSOURCES_H
    #include "my_radar.h"
    #include "structure.h"

typedef struct ressource_s ressource_t;

typedef enum {
    BACKGROUND
} assets_t;

typedef enum {
    TEXTURE,
    MUSIC,
} ressource_type_t;

struct ressource_s {
    void *ressource;
    ressource_type_t type;
    assets_t id;
};

linked_list_t *get_ressources_list(void);
ressource_t *create_ressources(const char *filepath, ressource_type_t type, assets_t id);
linked_list_t *destroy_ressources(linked_list_t *ressources_list);

#endif
