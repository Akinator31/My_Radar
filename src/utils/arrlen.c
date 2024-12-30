/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** my_arrlen
*/

#include <stdlib.h>

int arrlen(char **arr)
{
    int result = 0;

    for (int i = 0; arr[i] != NULL; i++) {
        result++;
    }
    return result;
}
