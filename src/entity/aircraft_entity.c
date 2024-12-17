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
    sfRenderWindow_drawSprite(engine->window, ((aircraft_t *)(aircraft_entity->data))->sprite, NULL);
}

void destroy_aircraft_entity(entity_t *aircraft_entity)
{
    sfSprite_destroy(((aircraft_t *)(aircraft_entity->data))->sprite);
    sfClock_destroy(((aircraft_t *)(aircraft_entity->data))->clock);
    free(aircraft_entity->data);
    free(aircraft_entity);
}

entity_t *create_aircraft_entity(sfTexture *texture, sfVector2f takeoff_pos, sfVector2f landing_pos)
{
    entity_t *aircraft_entity = malloc(sizeof(entity_t));
    aircraft_t *aircraft = malloc(sizeof(aircraft_t));

    aircraft->sprite = sfSprite_create();
    aircraft->takeoff_pos = takeoff_pos;
    aircraft->landing_pos = landing_pos;
    aircraft->clock = sfClock_create();
    sfSprite_setTexture(aircraft->sprite, texture, sfFalse);
    sfSprite_setPosition(aircraft->sprite, takeoff_pos);
    aircraft_entity->data = aircraft;
    aircraft_entity->entity_render = render_aircraft_entity;
    aircraft_entity->entity_update = NULL;
    aircraft_entity->entity_destroy = destroy_aircraft_entity;
    return aircraft_entity;
}