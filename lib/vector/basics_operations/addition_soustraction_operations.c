/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** vector
*/

#include "vector.h"

sfVector2f addition_by_float(sfVector2f original_vector, float value)
{
    return (sfVector2f){original_vector.x + value,
        original_vector.y + value};
}

sfVector2f addition_by_vector(sfVector2f original_vector,
    sfVector2f vector_to_add)
{
    return (sfVector2f){original_vector.x + vector_to_add.x,
        original_vector.y + vector_to_add.y};
}

sfVector2f subtraction_by_float(sfVector2f original_vector, float value)
{
    return (sfVector2f){original_vector.x - value,
        original_vector.y - value};
}

sfVector2f subtraction_by_vector(sfVector2f original_vector,
    sfVector2f vector_to_add)
{
    return (sfVector2f){original_vector.x - vector_to_add.x,
        original_vector.y - vector_to_add.y};
}
