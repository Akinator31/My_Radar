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

int tty_checker(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++) {
        if ((envp[i][0] == 'D') && (envp[i][1] == 'I') && envp[i][2] == 'S')
            return 1;
    }
    return 0;
}

int analyse_script_line(char *line)
{
    char **line_element = my_str_to_word_array(line);

    if (!is_char_of_char(line_element[0])) {
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

int script_file_content_inspection(FILE *script_file)
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

FILE *check_script_file(char **argv)
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
    return script_file;
}

engine_t *load_game(unsigned int default_framerate, char **envp, int ac, char **argv)
{
    engine_t *engine = malloc(sizeof(*engine));

    engine->script_file = check_script_file(argv);
    if (!tty_checker(envp) || (ac < 2) || (engine->script_file == NULL) || (ac > 2)) {
        free(engine);
        return NULL;
    }
    engine->window = create_window(WIDTH, HEIGTH, NAME);
    engine->clock = sfClock_create();
    engine->current_scene = NULL;
    engine->ressources = get_ressources_list();
    engine->scenes_list = load_scenes(engine, argv[2]);
    engine->delta_time = 0.0;
    engine->default_fps_framerate = default_framerate;
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
