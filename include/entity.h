/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** entity
*/

#ifndef INCLUDED_ENTITY_H
    #define INCLUDED_ENTITY_H
    #include "structure.h"

entity_t *create_entity(sfTexture *texture, sfVector2f pos, int id,
    void (*entity_update)(entity_t *entity, scene_t *scene, engine_t *engine));
entity_t *create_text(int text, sfVector2f pos, engine_t *engine);
void destroy_entity(entity_t *entity);

#endif
