/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** load_current_scene
*/

#include "engine.h"
#include "structure.h"

void load_current_scene(engine_t *engine)
{
    linked_list_t *temp = engine->scenes_list;

    while (temp != NULL) {
        if (((scene_t *)(temp->data))->id == engine->current_scene->id)
            ((scene_t *)(temp->data))->scene_render(temp->data, engine);
        temp = temp->next;
    }
}
