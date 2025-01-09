/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** complex_operation
*/

#include <math.h>
#include <stdio.h>
#include "vector.h"

float dot_product_vector(sfVector2f vector1, sfVector2f vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

float get_vector_length(sfVector2f vector)
{
    return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

sfVector2f normalize_vector(sfVector2f vector)
{
    float vector_lenght = get_vector_length(vector);

    if (vector_lenght == 0)
        return (sfVector2f){0, 0};
    return (sfVector2f){vector.x / vector_lenght, vector.y / vector_lenght};
}

sfVector2f get_normal_vector_left(sfVector2f vector)
{
    return normalize_vector((sfVector2f){- vector.y, vector.x});
}

sfVector2f get_normal_vector_right(sfVector2f vector)
{
    return normalize_vector((sfVector2f){vector.y, - vector.x});
}
