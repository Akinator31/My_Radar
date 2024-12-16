/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** engine
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "engine.h"
#include "my_lib.h"
#include "my_radar.h"
#include "structure.h"
#include "ressources.h"
#include "scenes.h"
#include "utils.h"

int tty_checker(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        if ((envp[i][0] == 'D') && (envp[i][1] == 'I') && envp[i][2] == 'S')
            return 1;
    }
    return 0;
}

engine_t *load_game(unsigned int default_framerate, char **envp)
{
    engine_t *engine = malloc(sizeof(*engine));

    if (!tty_checker(envp)) {
        free(engine);
        return NULL;
    }
    engine->window = create_window(WIDTH, HEIGTH, NAME);
    engine->clock = sfClock_create();
    engine->current_scene = NULL;
    engine->ressources = get_ressources_list();
    engine->scenes_list = load_scenes(engine);
    engine->state = RUNNING;
    engine->delta_time = 0.0;
    engine->default_fps_framerate = default_framerate;
    engine->music_state = PLAYING;
    engine->music_selector = MENU_MUSIC;
    sfRenderWindow_setFramerateLimit(engine->window,
        default_framerate);
    return engine;
}

void clean_scene(linked_list_t *list)
{
    linked_list_t *temp = list;

    while (temp != NULL) {
        ((scene_t *)temp->data)->scene_destroy(temp->data);
        temp = temp->next;
    }
    list = clear_list(list);
}

int engine_destroy(engine_t *engine)
{
    if (engine == NULL)
        return 84;
    clean_scene(engine->scenes_list);
    sfRenderWindow_destroy(engine->window);
    sfClock_destroy(engine->clock);
    destroy_ressources(engine->ressources);
    free(engine->ressources);
    free(engine);
    return 0;
}
