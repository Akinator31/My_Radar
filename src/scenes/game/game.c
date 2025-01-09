/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** game
*/

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "engine.h"
#include "scenes.h"
#include "entity.h"
#include "utils.h"
#include "quadtree.h"
#include "collisions.h"

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
        if ((temp->data != NULL) &&
            (((entity_t *)(temp->data))->state != DESTROY)) {
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
                                    (*temp)->data);
        *points_to_free = push_front_list(*points_to_free, point);
        insert_element(engine->quadtree, point);
    }
}

static void check_collisions(linked_list_t *one,
    linked_list_t *two, engine_t *engine)
{
    entity_t *aircraft_one_t = ((entity_t *)((point_t *)(one->data))->data);
    entity_t *aircraft_two_t = ((entity_t *)((point_t *)(two->data))->data);
    entity_t *tower_entity = NULL;
    linked_list_t *temp = engine->tower_list;

    if (one == two)
        return;
    while (temp != NULL) {
        tower_entity = ((entity_t *)(temp->data));
        if ((tower_entity->type == CONTROL_T) && check_tower_radius(
            aircraft_one_t, aircraft_two_t, tower_entity))
            return;
        temp = temp->next;
    }
    if (separate_axis_theorem(((aircraft_t *)(aircraft_one_t->data)),
        ((aircraft_t *)(aircraft_two_t->data)))) {
        aircraft_one_t->state = DESTROY;
        aircraft_two_t->state = DESTROY;
    }
}

static void apply_collisions(linked_list_t *aircraft_list, engine_t *engine)
{
    linked_list_t *aircraft = NULL;
    linked_list_t *other = NULL;

    if (aircraft_list == NULL)
        return;
    aircraft = aircraft_list;
    other = aircraft_list->next;
    while (aircraft != NULL) {
        while (other != NULL) {
            check_collisions(aircraft, other, engine);
            other = other->next;
        }
        aircraft = aircraft->next;
    }
}

static void manage_collisions(quadtree_t *quadtree, engine_t *engine)
{
    rectangle_t *range = NULL;
    linked_list_t *aircraft_entity_list = NULL;
    int counter = 0;

    if (quadtree == NULL)
        return;
    range = get_rectangle_with_offset(quadtree->boundary, 0);
    aircraft_entity_list = lauch_query(quadtree, range,
        aircraft_entity_list, &counter);
    free(range);
    if (counter > 1)
        apply_collisions(aircraft_entity_list, engine);
    aircraft_entity_list = clear_list(aircraft_entity_list);
    manage_collisions(quadtree->northeast, engine);
    manage_collisions(quadtree->northwest, engine);
    manage_collisions(quadtree->southeast, engine);
    manage_collisions(quadtree->southwest, engine);
}

int update_game_page(scene_t *scene, engine_t *engine)
{
    rectangle_t *boundary = NULL;
    linked_list_t *temp = scene->entity_list;
    linked_list_t *points_to_free = NULL;

    if (get_number_of_plane(scene->entity_list) == 0)
        return 84;
    boundary = create_rectangle(0, 0, 1920, 1080);
    engine->quadtree = create_quadtree(boundary, 5, 7);
    while (temp != NULL) {
        manage_quadtree(&temp, &points_to_free, engine, scene);
        temp = temp->next;
    }
    manage_collisions(engine->quadtree, engine);
    if (engine->show_quadtree)
        display_rectangle(engine->window, engine->quadtree);
    clear_list_and_data(points_to_free, free);
    destroy_quadtree(engine->quadtree);
    engine->quadtree = NULL;
    return 0;
}

static linked_list_t *get_tower_list(linked_list_t *list)
{
    linked_list_t *temp = list;
    linked_list_t *result = NULL;
    entity_t *temp1 = NULL;

    while (temp != NULL) {
        temp1 = ((entity_t *)(temp->data));
        if (temp1->type == CONTROL_T) {
            result = push_front_list(result, temp->data);
        }
        temp = temp->next;
    }
    return result;
}

scene_t *init_game_scene(engine_t *engine)
{
    linked_list_t *entity_list = new_list();
    scene_t *game_scene = malloc(sizeof(scene_t));

    srand(time(NULL));
    entity_list = push_front_list(entity_list,
        create_image_entity(GET_RES(BACKGROUND)->ressource, POS(0, 0)));
    entity_list = load_entities(entity_list, engine);
    engine->tower_list = get_tower_list(entity_list);
    game_scene->id = 0;
    game_scene->clock = sfClock_create();
    game_scene->entity_list = entity_list;
    game_scene->scene_render = &render_game_page;
    game_scene->scene_update = &update_game_page;
    game_scene->scene_destroy = &destroy_game_page;
    engine->current_scene = game_scene;
    return game_scene;
}
