/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** aircraft_entity
*/

#include <stdlib.h>
#include "ressources.h"
#include "entity.h"
#include "utils.h"

void render_aircraft_entity(entity_t *aircraft_entity, engine_t *engine)
{
    sfRectangleShape *hitbox = PLANE->hitbox;
    sfVector2f hitbox_size = {20, 20};
    sfVector2f origin_size = {hitbox_size.x / 2, hitbox_size.y / 2};

    if (engine->show_sprite) {
        sfSprite_setOrigin(PLANE->sprite, origin_size);
        sfRenderWindow_drawSprite(engine->window, PLANE->sprite, NULL);
    }
    if (engine->show_sprite && engine->show_hitbox) {
        sfRectangleShape_setSize(hitbox, hitbox_size);
        sfRectangleShape_setPosition(hitbox, PLANE->position);
        sfRectangleShape_setOrigin(hitbox, origin_size);
        sfRectangleShape_setOutlineColor(hitbox, sfRed);
        sfRectangleShape_setOutlineThickness(hitbox, 2);
        sfRectangleShape_setFillColor(hitbox, sfTransparent);
        sfRenderWindow_drawRectangleShape(engine->window, hitbox, NULL);
    }
}

void destroy_aircraft_entity(entity_t *aircraft_entity)
{
    sfSprite_destroy(PLANE->sprite);
    sfClock_destroy(PLANE->clock);
    sfRectangleShape_destroy(PLANE->hitbox);
    free(aircraft_entity->data);
    free(aircraft_entity);
}

entity_t *create_aircraft_entity(sfTexture *texture,
    sfVector2f takeoff_pos, sfVector2f landing_pos)
{
    entity_t *aircraft_entity = malloc(sizeof(entity_t));
    aircraft_t *aircraft = malloc(sizeof(aircraft_t));

    aircraft->sprite = sfSprite_create();
    aircraft->position = takeoff_pos;
    aircraft->takeoff_pos = takeoff_pos;
    aircraft->landing_pos = landing_pos;
    aircraft->clock = sfClock_create();
    aircraft->hitbox = sfRectangleShape_create();
    sfSprite_setTexture(aircraft->sprite, texture, sfFalse);
    sfSprite_setPosition(aircraft->sprite, takeoff_pos);
    aircraft_entity->data = aircraft;
    aircraft_entity->entity_render = render_aircraft_entity;
    aircraft_entity->entity_update = NULL;
    aircraft_entity->entity_destroy = destroy_aircraft_entity;
    return aircraft_entity;
}
