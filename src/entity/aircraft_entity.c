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

linked_list_t *update_aircraft_entity(linked_list_t *node,
    entity_t *aircraft_entity, scene_t *scene)
{
    if ((aircraft_entity->state == ACTIVE) && plane_has_arrived(PLANE)) {
            aircraft_entity->state = DESTROY;
            sfClock_destroy(PLANE->clock);
            sfRectangleShape_destroy(PLANE->hitbox);
            sfSprite_destroy(PLANE->sprite);
            sfClock_destroy(PLANE->position_clock);
            free(aircraft_entity->data);
            free(aircraft_entity);
            return delete_node(&scene->entity_list, node);
        }
    if ((aircraft_entity != NULL) && (aircraft_entity->state == DESTROY)) {
        sfRectangleShape_destroy(PLANE->hitbox);
        sfSprite_destroy(PLANE->sprite);
        sfClock_destroy(PLANE->clock);
        sfClock_destroy(PLANE->position_clock);
        free(aircraft_entity->data);
        free(aircraft_entity);
        return delete_node(&scene->entity_list, node);
    }
    return node;
}

static void hitbox_manager(entity_t *aircraft_entity, engine_t *engine)
{
    sfRectangleShape *hitbox = PLANE->hitbox;
    sfVector2f hitbox_size = {20, 20};

    if ((aircraft_entity != NULL) && (aircraft_entity->state == ACTIVE)) {
        if (engine->show_sprite) {
            sfRenderWindow_drawSprite(engine->window, PLANE->sprite, NULL);
        }
        if (engine->show_hitbox) {
            sfRectangleShape_setSize(hitbox, hitbox_size);
            sfRectangleShape_setOutlineColor(hitbox, sfRed);
            sfRectangleShape_setOutlineThickness(hitbox, 2);
            sfRectangleShape_setFillColor(hitbox, sfTransparent);
            sfRenderWindow_drawRectangleShape(engine->window, hitbox, NULL);
        }
    }
}

static void move_aircraft(entity_t *aircraft_entity)
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
    if ((aircraft_entity != NULL) && (aircraft_entity->state == PREPARE) &&
        (sfTime_asSeconds(sfClock_getElapsedTime(engine->clock))
        >= PLANE->offset_takeoff)) {
        PLANE->clock = sfClock_create();
        PLANE->position_clock = sfClock_create();
        aircraft_entity->state = ACTIVE;
    }
    if ((aircraft_entity != NULL) && (aircraft_entity->state == ACTIVE) &&
        (sfTime_asSeconds(sfClock_getElapsedTime(engine->clock))
        >= PLANE->offset_takeoff)) {
        hitbox_manager(aircraft_entity, engine);
        move_aircraft(aircraft_entity);
    }
}

void destroy_aircraft_entity(entity_t *aircraft_entity)
{
    if (aircraft_entity->state == ACTIVE) {
        sfSprite_destroy(PLANE->sprite);
        sfRectangleShape_destroy(PLANE->hitbox);
        sfClock_destroy(PLANE->clock);
        sfClock_destroy(PLANE->position_clock);
        free(aircraft_entity->data);
        free(aircraft_entity);
    } else if ((aircraft_entity->state == PREPARE)
        || (aircraft_entity->state == DESTROY)) {
        sfSprite_destroy(PLANE->sprite);
        sfRectangleShape_destroy(PLANE->hitbox);
        free(aircraft_entity->data);
        free(aircraft_entity);
    } else {
        free(aircraft_entity);
    }
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
    aircraft->hitbox = sfRectangleShape_create();
    set_sprite_rotation(aircraft, takeoff_pos, landing_pos);
    sfSprite_setTexture(aircraft->sprite, texture, sfFalse);
    sfSprite_setPosition(aircraft->sprite, takeoff_pos);
    aircraft_entity->type = AIRPLANE;
    aircraft_entity->data = aircraft;
    aircraft_entity->state = PREPARE;
    aircraft_entity->entity_render = render_aircraft_entity;
    aircraft_entity->entity_update = update_aircraft_entity;
    aircraft_entity->entity_destroy = destroy_aircraft_entity;
    return aircraft_entity;
}
