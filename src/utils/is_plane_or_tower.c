/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** is_char_of_char
*/

#include <stdlib.h>

int is_a_char(char actual_char)
{
    if ((actual_char == 'A') || (actual_char == 'T'))
        return 1;
    return 0;
}

int is_plane_or_tower(char *buffer)
{
    if (buffer == NULL)
        return 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (!is_a_char(buffer[i]))
            return 0;
    }
    return 1;
}
