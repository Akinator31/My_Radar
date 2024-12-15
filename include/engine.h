/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** engine
*/

#ifndef INCLUDED_ENGINE_H
    #define INCLUDED_ENGINE_H
    #include "my_lib.h"
    #include "my_radar.h"
    #include "structure.h"
    #include "ressources.h"

engine_t *load_game(unsigned int default_framerate, char **envp);
int engine_destroy(engine_t *engine);
void load_current_scene(engine_t *engine);

#endif
