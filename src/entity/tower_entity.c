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
    sfRenderWindow_drawSprite(engine->window, ((control_tower_t *)(tower_entity->data))->sprite, NULL);
}

void destroy_tower_entity(entity_t *tower_entity)
{
    sfSprite_destroy(((control_tower_t *)(tower_entity->data))->sprite);
    free(tower_entity->data);
    free(tower_entity);
}

entity_t *create_tower_entity(sfTexture *texture, sfVector2f pos)
{
    entity_t *tower_entity = malloc(sizeof(entity_t));
    control_tower_t *tower = malloc(sizeof(control_tower_t));

    tower->sprite = sfSprite_create();
    tower->pos = pos;
    sfSprite_setTexture(tower->sprite, texture, sfFalse);
    sfSprite_setPosition(tower->sprite, pos);
    tower_entity->data = tower;
    tower_entity->entity_render = render_tower_entity;
    tower_entity->entity_update = NULL;
    tower_entity->entity_destroy = destroy_tower_entity;
    return tower_entity;
}