/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** switch_music
*/

#include "structure.h"
#include "engine.h"

void switch_pause_music(engine_t *engine)
{
    if (engine->music_selector == PAUSE &&
        engine->music_state == PLAYING) {
        sfMusic_pause(engine->ressources->game_music);
    }
}

void switch_game_music(engine_t *engine)
{
    if (((engine->music_selector == MENU_MUSIC) ||
        engine->music_selector == PAUSE) &&
        engine->music_state == PLAYING) {
        sfMusic_stop(GET_RES(menu_music));
        sfMusic_play(GET_RES(game_music));
        engine->music_selector = GAME_MUSIC;
    }
}

void switch_menu_music(engine_t *engine)
{
    if (engine->music_selector == GAME_MUSIC &&
        engine->music_state == PLAYING) {
        sfMusic_stop(GET_RES(game_music));
        sfMusic_play(GET_RES(menu_music));
        engine->music_selector = MENU_MUSIC;
    }
}
