/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** main
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "my_radar.h"
#include "structure.h"
#include "engine.h"
#include "scenes.h"
#include "event.h"
#include "utils.h"

int main(int ac, char **av, char **envp)
{
    engine_t *engine;

    if (ac > 1)
        return help(ac, av);
    engine = load_game(60, envp);
    while ((engine != NULL) && sfRenderWindow_isOpen(engine->window)) {
        sfRenderWindow_clear(engine->window, sfBlack);
        load_current_scene(engine);
        if (engine->state == RUNNING && ((scene_t *)(engine->current_scene))
            ->scene_update(engine->current_scene, engine) == 84)
            return engine_destroy(engine);
        while (sfRenderWindow_pollEvent(engine->window, &engine->event))
            analyse_event(engine->window, &engine->event);
        sfRenderWindow_display(engine->window);
    }
    return engine_destroy(engine);
}
