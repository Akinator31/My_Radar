/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** game
*/

scene_t *init_game_scene(engine_t *engine)
{
    linked_list_t *entity_list = new_list();
    scene_t *game_scene = malloc(sizeof(scene_t));

    srand(time(NULL));
    sfMusic_setLoop(GET_RES(game_music), sfTrue);
    entity_list = push_front_list_all(entity_list, 4,
        create_entity(GET_RES(quit_button), POS(30, 30), 3, NULL),
        create_entity(GET_RES(pause_button), POS(1739, 30), 2, NULL),
        create_text(0, POS(1200, 40), engine),
        create_entity(GET_RES(game_background), POS(0, 0), 1, NULL));
    game_scene->id = 3;
    game_scene->clock = sfClock_create();
    game_scene->entity_list = entity_list;
    game_scene->scene_render = &render_game_scene;
    game_scene->scene_update = &update_game_scene;
    game_scene->scene_pause_update = &update_pause_game;
    game_scene->scene_destroy = &destroy_game_scene;
    return game_scene;
}