/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** script_inspection
*/

#include <stdio.h>

int script_inspection(int ac, char **av)
{
    FILE *file = fopen(av[2], "r");

    if (file == NULL)
        return 84;
}