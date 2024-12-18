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
typedef struct control_tower_s control_tower_t;

struct image_s {
    sfSprite *sprite;
    sfVector2f pos;
};

struct aircraft_s {
    sfSprite *sprite;
    sfVector2f position;
    sfVector2f takeoff_pos;
    sfVector2f landing_pos;
    sfClock *clock;
    sfRectangleShape *hitbox;
    int offset_takeoff;
    int velocity;
};

struct control_tower_s {
    sfSprite *sprite;
    sfVector2f pos;
    sfCircleShape *controlable_zone;
    int radius;
};

typedef enum entity_type_s {
    IMAGE
} entity_type_t;

linked_list_t *load_entities(linked_list_t *entity_list, engine_t *engine);
entity_t *create_image_entity(sfTexture *texture, sfVector2f pos);
entity_t *create_aircraft_entity(sfTexture *texture, sfVector2f takeoff_pos,
    sfVector2f landing_pos);
entity_t *create_tower_entity(sfTexture *texture, sfVector2f pos, int radius);

#endif
