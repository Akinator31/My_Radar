/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** tower_entity
*/

#include <stdlib.h>
#include "ressources.h"
#include "entity.h"
#include "utils.h"

void render_tower_entity(entity_t *tower_entity, engine_t *engine)
{
    sfCircleShape *control_radius = TOWER->controlable_zone;
    sfVector2f control_radius_pos = TOWER->pos;
    int radius = TOWER->radius;

    if (engine->show_sprite)
        sfRenderWindow_drawSprite(engine->window, TOWER->sprite, NULL);
    if (engine->show_sprite && engine->show_hitbox) {
        sfCircleShape_setRadius(control_radius, radius);
        sfCircleShape_setFillColor(control_radius, sfTransparent);
        control_radius_pos.x += sfCircleShape_getRadius(control_radius);
        control_radius_pos.y += sfCircleShape_getRadius(control_radius);
        sfSprite_setOrigin(TOWER->sprite, SF_VECTOR_2F(37.5, 37.5));
        sfCircleShape_setOrigin(control_radius, SF_VECTOR_2F(radius, radius));
        sfCircleShape_setPosition(control_radius, TOWER->pos);
        sfCircleShape_setOutlineColor(control_radius, sfRed);
        sfCircleShape_setOutlineThickness(control_radius, 2);
        sfRenderWindow_drawCircleShape(engine->window, control_radius, NULL);
    }
}

void destroy_tower_entity(entity_t *tower_entity)
{
    sfSprite_destroy(TOWER->sprite);
    sfCircleShape_destroy(TOWER->controlable_zone);
    free(tower_entity->data);
    free(tower_entity);
}

entity_t *create_tower_entity(sfTexture *texture, sfVector2f pos, int radius)
{
    entity_t *tower_entity = malloc(sizeof(entity_t));
    control_tower_t *tower = malloc(sizeof(control_tower_t));

    tower->sprite = sfSprite_create();
    tower->pos = pos;
    sfSprite_setTexture(tower->sprite, texture, sfFalse);
    sfSprite_setPosition(tower->sprite, pos);
    tower->radius = radius;
    tower->controlable_zone = sfCircleShape_create();
    tower_entity->data = tower;
    tower_entity->entity_render = render_tower_entity;
    tower_entity->entity_update = NULL;
    tower_entity->entity_destroy = destroy_tower_entity;
    return tower_entity;
}
