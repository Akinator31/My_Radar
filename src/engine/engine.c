/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** engine
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.h>
#include "engine.h"
#include "my_lib.h"
#include "my_radar.h"
#include "structure.h"
#include "ressources.h"
#include "scenes.h"
#include "utils.h"
#include "errors.h"

static int tty_checker(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        if ((envp[i][0] == 'D') && (envp[i][1] == 'I') && envp[i][2] == 'S')
            return 1;
    }
    return 0;
}

static int analyse_script_line(char *line)
{
    char **line_element = my_str_to_word_array(line);

    if (!is_plane_or_tower(line_element[0])) {
        free_2d_array_of_char(line_element);
        return 0;
    }
    if (((my_strcmp(line_element[0], "A") == 0) && (arrlen(line_element) != 7))
        || ((my_strcmp(line_element[0], "T") == 0) &&
        (arrlen(line_element) != 4))) {
        free_2d_array_of_char(line_element);
        return 0;
    }
    for (int i = 1; line_element[i] != NULL; i++) {
        if (!is_char_of_number(line_element[i])) {
            free_2d_array_of_char(line_element);
            return 0;
        }
    }
    free_2d_array_of_char(line_element);
    return 1;
}

static int script_file_content_inspection(FILE *script_file)
{
    char *buffer = NULL;
    size_t len = 0;

    while (getline(&buffer, &len, script_file) != -1) {
        if (!analyse_script_line(buffer)) {
            free(buffer);
            return 0;
        }
    }
    free(buffer);
    return 1;
}

static char *check_script_file(char **argv)
{
    FILE *script_file = fopen(argv[1], "r");

    if (script_file == NULL) {
        errors_manager(INVALID_SCRIPT_FILE);
        return NULL;
    }
    if (!script_file_content_inspection(script_file)) {
        errors_manager(INVALID_SCRIPT_CONTENT);
        return NULL;
    }
    return argv[1];
}

engine_t *load_game(unsigned int default_framerate,
    char **envp, int ac, char **argv)
{
    engine_t *engine = malloc(sizeof(*engine));

    engine->script_path = check_script_file(argv);
    if (!tty_checker(envp) || (ac < 2) ||
        (engine->script_path == NULL) || (ac > 2)) {
        free(engine);
        return NULL;
    }
    engine->window = create_window(WIDTH, HEIGTH, NAME);
    engine->clock = sfClock_create();
    engine->current_scene = NULL;
    engine->ressources = get_ressources_list();
    engine->scenes_list = load_scenes(engine);
    engine->default_fps_framerate = default_framerate;
    engine->show_hitbox = true;
    engine->show_sprite = true;
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
    free(engine);
    return 0;
}
