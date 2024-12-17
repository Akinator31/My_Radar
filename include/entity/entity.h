/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** entity
*/

#ifndef INCLUDED_ENTITY_H
    #define INCLUDED_ENTITY_H
    #include "structure.h"
    #include "ressources.h"

typedef struct image_s image_t;
typedef struct aircraft_s aircraft_t;
typedef enum entity_type_s entity_type_t;

struct image_s {
    sfSprite *sprite;
    sfVector2f pos;
};

struct aircraft_s {
    sfSprite *sprite;
    sfVector2f takeoff_pos;
    sfVector2f landing_pos;

};

enum entity_type_s {
    IMAGE
};

entity_t *create_entity(sfTexture *texture, sfVector2f pos, int id,
    void (*entity_update)(entity_t *entity, scene_t *scene, engine_t *engine));
entity_t *create_text(int text, sfVector2f pos);
void destroy_entity(entity_t *entity);
linked_list_t *create_aircrafts(linked_list_t *entity_list, FILE *script_file);
entity_t *create_image_entity(sfTexture *texture, sfVector2f pos);

#endif
