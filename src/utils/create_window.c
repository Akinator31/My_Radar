/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** create_window
*/

#include "my_hunter.h"

sfRenderWindow *create_window(unsigned int width,
    unsigned int heigth, char *window_title)
{
    sfVideoMode video_mode = {width, heigth, 32};
    sfRenderWindow *window = sfRenderWindow_create(
        video_mode, window_title, sfClose, NULL);

    return window;
}
