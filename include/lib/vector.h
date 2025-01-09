/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** vector
*/

#ifndef INCLUDED_VECTOR_H
    #define INCLUDED_VECTOR_H
    #include <SFML/Graphics.h>

sfVector2f addition_by_float(sfVector2f original_vector, float value);
sfVector2f addition_by_vector(sfVector2f original_vector,
    sfVector2f vector_to_add);
sfVector2f subtraction_by_float(sfVector2f original_vector, float value);
sfVector2f subtraction_by_vector(sfVector2f original_vector,
    sfVector2f vector_to_add);
sfVector2f multiplication_by_float(sfVector2f original_vector, float value);
sfVector2f multiplication_by_vector(sfVector2f original_vector,
    sfVector2f vector_to_add);
sfVector2f division_by_float(sfVector2f original_vector, float value);
sfVector2f division_by_vector(sfVector2f original_vector,
    sfVector2f vector_to_add);
float dot_product_vector(sfVector2f vector1, sfVector2f vector2);
float get_vector_lenght(sfVector2f vector);
sfVector2f normalize_vector(sfVector2f vector);
sfVector2f get_normal_vector_left(sfVector2f vector);
sfVector2f get_normal_vector_right(sfVector2f vector);

#endif
