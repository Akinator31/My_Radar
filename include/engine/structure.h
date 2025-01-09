/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** structure
*/

#ifndef INCLUDED_STRUCTURE_H
    #define INCLUDED_STRUCTURE_H
    #include <SFML/Graphics.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include "my_list.h"
    #include "my_lib.h"
    #include "quadtree.h"
    #define POS(x, y) ((sfVector2f){(x), (y)})
    #define TX_CREATE(res, i) res = sfTexture_createFromFile(assets[i], NULL)
    #define GET_RES(id) get_ressource_by_id(engine->ressources, id)
    #define GET_SPRITE() ((entity_t *)(temp->data))->sprite
    #define PLANE ((aircraft_t *)(aircraft_entity->data))
    #define TOWER ((control_tower_t *)(tower_entity->data))
    #define SF_VECTOR_2U(x, y) ((sfVector2u){(x), (y)})
    #define SF_VECTOR_2I(x, y) ((sfVector2i){(x), (y)})
    #define SF_VECTOR_2F(x, y) ((sfVector2f){(x), (y)})

typedef struct engine_s engine_t;
typedef struct scene_s scene_t;
typedef struct entity_s entity_t;
typedef struct ressource_manager_s ressource_manager_t;

enum entity_state {
    ACTIVE,
    DESTROY,
    PREPARE,
};

enum entity_type {
    AIRPLANE,
    CONTROL_T,
    IMAGE_T
};

struct engine_s {
    sfRenderWindow *window;
    sfClock *clock;
    scene_t *current_scene;
    linked_list_t *scenes_list;
    linked_list_t *ressources;
    sfEvent event;
    quadtree_t *quadtree;
    linked_list_t *tower_list;
    char *script_path;
    int default_fps_framerate;
    bool show_hitbox;
    bool show_sprite;
    bool show_quadtree;
};

struct scene_s {
    int id;
    linked_list_t *entity_list;
    linked_list_t *tower_list;
    sfClock *clock;
    int (*scene_update)(scene_t *scene, engine_t *engine);
    void (*scene_render)(scene_t *scene, engine_t *engine);
    void (*scene_pause_update)(scene_t *scene, engine_t *engine);
    void (*scene_destroy)(scene_t *scene);
};

struct entity_s {
    enum entity_state state;
    void *data;
    void (*entity_render)(entity_t *entity, engine_t *engine);
    linked_list_t *(*entity_update)(linked_list_t *node,
        entity_t *entity, scene_t *scene);
    void (*entity_destroy)(entity_t *entity);
    enum entity_type type;
};

#endif
