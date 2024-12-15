/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** event_manager
*/

#include <SFML/Graphics.h>

void analyse_event(sfRenderWindow *window, sfEvent *event)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window);
}
