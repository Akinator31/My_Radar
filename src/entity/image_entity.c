/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** image
*/

#include <stdlib.h>
#include "ressources.h"
#include "entity.h"
#include "utils.h"

void render_image_entity(entity_t *image_entity, engine_t *engine)
{
    sfRenderWindow_drawSprite(engine->window,
        ((image_t *)(image_entity->data))->sprite, NULL);
}

void destroy_image_entity(entity_t *image_entity)
{
    sfSprite_destroy(((image_t *)(image_entity->data))->sprite);
    free(image_entity->data);
    free(image_entity);
}

entity_t *create_image_entity(sfTexture *texture, sfVector2f pos)
{
    entity_t *image_entity = malloc(sizeof(entity_t));
    image_t *image = malloc(sizeof(image_t));

    image->pos = pos;
    image->sprite = sfSprite_create();
    sfSprite_setTexture(image->sprite, texture, sfFalse);
    image_entity->data = image;
    image_entity->entity_render = render_image_entity;
    image_entity->entity_update = NULL;
    image_entity->entity_destroy = destroy_image_entity;
    image_entity->state = ACTIVE;
    image_entity->type = IMAGE_T;
    return image_entity;
}
