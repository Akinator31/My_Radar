/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** entity
*/

#include <stdlib.h>
#include "structure.h"
#include "entity.h"

void destroy_entity(entity_t *entity)
{
    sfSprite_destroy(entity->sprite);
    sfClock_destroy(entity->clock);
    free(entity);
}

void destroy_text_entity(entity_t *entity)
{
    sfText_destroy(entity->text);
    sfClock_destroy(entity->clock);
    free(entity);
}

entity_t *create_entity(sfTexture *texture, sfVector2f pos, int id,
    void (*entity_update)(entity_t *entity, scene_t *scene, engine_t *engine))
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->sprite = sfSprite_create();
    entity->pos = pos;
    entity->id = id;
    entity->entity_destroy = &destroy_entity;
    entity->entity_update = entity_update;
    entity->state = ACTIVE;
    entity->clock = sfClock_create();
    sfSprite_setTexture(entity->sprite, texture, sfFalse);
    sfSprite_setTextureRect(entity->sprite,
        sfSprite_getTextureRect(entity->sprite));
    sfSprite_setPosition(entity->sprite, pos);
    return entity;
}

entity_t *create_text(int text, sfVector2f pos, engine_t *engine)
{
    entity_t *entity = malloc(sizeof(entity_t));
    sfColor orange = sfColor_fromRGB(254, 116, 15);
    char *text_num = my_strnum(text);

    entity->is_text = 1;
    entity->text = sfText_create();
    entity->clock = sfClock_create();
    entity->entity_destroy = &destroy_text_entity;
    sfText_setString(entity->text, text_num);
    sfText_setPosition(entity->text, pos);
    sfText_setFont(entity->text, engine->ressources->font);
    sfText_setStyle(entity->text, sfTextBold);
    sfText_setColor(entity->text, orange);
    sfText_setCharacterSize(entity->text, 100);
    free(text_num);
    return entity;
}
