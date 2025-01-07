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
#include "quadtree.h"

static void display_rectangle(sfRenderWindow *window, quadtree_t *quadtree)
{
    sfRectangleShape *rect = NULL;

    if (!quadtree)
        return;
    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f){quadtree->boundary->w,
        quadtree->boundary->h});
    sfRectangleShape_setPosition(rect, (sfVector2f){quadtree->boundary->x,
        quadtree->boundary->y});
    sfRectangleShape_setOutlineColor(rect, sfRed);
    sfRectangleShape_setOutlineThickness(rect, 2);
    sfRectangleShape_setFillColor(rect, sfTransparent);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
    sfRectangleShape_destroy(rect);
    display_rectangle(window, quadtree->northwest);
    display_rectangle(window, quadtree->northeast);
    display_rectangle(window, quadtree->southwest);
    display_rectangle(window, quadtree->southeast);
};

void render_game_page(scene_t *scene, engine_t *engine)
{
    linked_list_t *temp = scene->entity_list;

    while (temp != NULL) {
        if (temp->data != NULL) {
            ((entity_t *)(temp->data))->entity_render(temp->data, engine);
        }
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

void manage_quadtree(linked_list_t **temp, linked_list_t **points_to_free,
    engine_t *engine, scene_t *scene)
{
    aircraft_t *aircraft_entity = NULL;
    point_t *point = NULL;

    if (((((entity_t *)((*temp)->data))->entity_update != NULL) &&
        ((*temp)->data != NULL))) {
        *temp = ((entity_t *)((*temp)->data))->
        entity_update(*temp, (*temp)->data, scene);
    }
    if (*temp == NULL)
        return;
    if (((((entity_t *)((*temp)->data))->entity_update != NULL) &&
        ((*temp)->data != NULL)) && (((entity_t *)((*temp)->data))->state
        == ACTIVE)) {
        aircraft_entity = ((entity_t *)((*temp)->data))->data;
        point = create_point(aircraft_entity->position.x,
                                    aircraft_entity->position.y,
                                    aircraft_entity->hitbox);
        *points_to_free = push_front_list(*points_to_free, point);
        insert_element(engine->quadtree, point);
    }
}

int update_game_page(scene_t *scene, engine_t *engine)
{
    rectangle_t *boundary = create_rectangle(0, 0, 1920, 1080);
    linked_list_t *temp = scene->entity_list;
    linked_list_t *points_to_free = NULL;

    engine->quadtree = create_quadtree(boundary, 4, 6);
    while (temp != NULL) {
        manage_quadtree(&temp, &points_to_free, engine, scene);
        if (temp != NULL)
            temp = temp->next;
    }
    if (engine->show_quadtree)
        display_rectangle(engine->window, engine->quadtree);
    clear_list_and_data(points_to_free, free);
    destroy_quadtree(engine->quadtree);
    engine->quadtree = NULL;
    return 0;
}

scene_t *init_game_scene(engine_t *engine)
{
    linked_list_t *entity_list = new_list();
    scene_t *game_scene = malloc(sizeof(scene_t));

    srand(time(NULL));
    entity_list = push_front_list_all(entity_list, 1,
        create_image_entity(GET_RES(BACKGROUND)->ressource, POS(0, 0)));
    entity_list = load_entities(entity_list, engine);
    game_scene->id = 0;
    game_scene->clock = sfClock_create();
    game_scene->entity_list = entity_list;
    game_scene->scene_render = &render_game_page;
    game_scene->scene_update = &update_game_page;
    game_scene->scene_destroy = &destroy_game_page;
    engine->current_scene = game_scene;
    return game_scene;
}
