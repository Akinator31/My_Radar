/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** aircraft_entity
*/

#include <stdlib.h>
#include <math.h>
#include "ressources.h"
#include "entity.h"
#include "utils.h"

static void hitbox_manager(entity_t *aircraft_entity, engine_t *engine)
{
    sfRectangleShape *hitbox = PLANE->hitbox;
    sfVector2f hitbox_size = {20, 20};

    if (engine->show_sprite)
        sfRenderWindow_drawSprite(engine->window, PLANE->sprite, NULL);
    if (engine->show_sprite && engine->show_hitbox) {
        sfRectangleShape_setSize(hitbox, hitbox_size);
        sfRectangleShape_setOutlineColor(hitbox, sfRed);
        sfRectangleShape_setOutlineThickness(hitbox, 2);
        sfRectangleShape_setFillColor(hitbox, sfTransparent);
        sfRenderWindow_drawRectangleShape(engine->window, hitbox, NULL);
    }
}

void move_aircraft(entity_t *aircraft_entity)
{
    float delta_time = sfTime_asSeconds(sfClock_restart(PLANE->clock));
    float distance = PLANE->velocity * delta_time;
    float radians = PLANE->direction_angle * (M_PI / 180);
    sfVector2f new_pos = {
        PLANE->position.x + distance * cos(radians),
        PLANE->position.y + distance * sin(radians)};

    PLANE->position = new_pos;
    sfSprite_setPosition(PLANE->sprite, new_pos);
    sfRectangleShape_setPosition(PLANE->hitbox,
        new_pos);
}

void render_aircraft_entity(entity_t *aircraft_entity, engine_t *engine)
{
    if (sfTime_asSeconds(sfClock_getElapsedTime(engine->clock)) >=
        PLANE->offset_takeoff) {
        hitbox_manager(aircraft_entity, engine);
        move_aircraft(aircraft_entity);
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

void set_sprite_rotation(aircraft_t *aircraft,
    sfVector2f takeoff_pos, sfVector2f landing_pos)
{
    float x = landing_pos.x - takeoff_pos.x;
    float y = landing_pos.y - takeoff_pos.y;
    float angle = atan2(y, x) * (180 / M_PI);

    sfSprite_setRotation(aircraft->sprite, angle);
    sfRectangleShape_setRotation(aircraft->hitbox, angle);
    sfRectangleShape_setPosition(aircraft->hitbox, aircraft->takeoff_pos);
    aircraft->direction_angle = angle;
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
    set_sprite_rotation(aircraft, takeoff_pos, landing_pos);
    sfSprite_setTexture(aircraft->sprite, texture, sfFalse);
    sfSprite_setPosition(aircraft->sprite, takeoff_pos);
    aircraft_entity->data = aircraft;
    aircraft_entity->entity_render = render_aircraft_entity;
    aircraft_entity->entity_update = NULL;
    aircraft_entity->entity_destroy = destroy_aircraft_entity;
    return aircraft_entity;
}
