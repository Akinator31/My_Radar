/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** game
*/

#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "scenes.h"
#include "entity.h"
#include "utils.h"

void render_game_page(scene_t *scene, engine_t *engine)
{
    linked_list_t *temp = scene->entity_list;

    while (temp != NULL) {
        ((entity_t *)(temp->data))->entity_render(temp->data, engine);
        temp = temp->next;
    }
}

void destroy_game_page(scene_t *scene)
{
    linked_list_t *temp = scene->entity_list;

    for (int i = 0; temp != NULL; i++) {
        ((entity_t *)temp->data)->entity_destroy(temp->data);
        temp = temp->next;
    }
    sfClock_destroy(scene->clock);
    scene->entity_list = clear_list(scene->entity_list);
    free(scene);
}

int update_game_page(scene_t *scene, engine_t *engine)
{
    linked_list_t *temp = scene->entity_list;

    while (temp != NULL) {
        if ((((entity_t *)(temp->data))->entity_update != NULL))
            ((entity_t *)(temp->data))->entity_update(temp->data, scene, engine);
        temp = temp->next;
    }
    return 0;
}

scene_t *init_game_scene(engine_t *engine, char *script_path)
{
    linked_list_t *entity_list = new_list();
    scene_t *game_scene = malloc(sizeof(scene_t));

    srand(time(NULL));
    entity_list = push_front_list_all(entity_list, 1,
        create_image_entity(GET_RES(BACKGROUND)->ressource, POS(0, 0)));
    //entity_list = create_aircrafts(entity_list);
    game_scene->id = 0;
    game_scene->clock = sfClock_create();
    game_scene->entity_list = entity_list;
    game_scene->scene_render = &render_game_page;
    game_scene->scene_update = &update_game_page;
    game_scene->scene_destroy = &destroy_game_page;
    engine->current_scene = game_scene;
    return game_scene;
}
