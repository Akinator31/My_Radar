/*
** EPITECH PROJECT, 2025
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** collisions
*/

#include <math.h>
#include <stdlib.h>
#include "entity.h"
#include "vector.h"
#include "utils.h"

static float get_max_dot_product(float dot_product_arr[], int nb_value)
{
    float max_value = dot_product_arr[0];

    for (int i = 0; i < nb_value; i++) {
        if (dot_product_arr[i] > max_value)
            max_value = dot_product_arr[i];
    }
    return max_value;
}

static float get_min_dot_product(float dot_product_arr[], int nb_value)
{
    float min_value = dot_product_arr[0];

    for (int i = 0; i < nb_value; i++) {
        if (dot_product_arr[i] < min_value)
            min_value = dot_product_arr[i];
    }
    return min_value;
}

sfVector2f rotate_point(sfVector2f point, sfVector2f center, float angle)
{
    float radian = angle * (M_PI / 180.0);
    sfVector2f rotated;

    rotated.x = cos(radian) * (point.x - center.x) - sin(radian)
        * (point.y - center.y) + center.x;
    rotated.y = sin(radian) * (point.x - center.x) + cos(radian)
        * (point.y - center.y) + center.y;
    return rotated;
}

static sfVector2f *get_shape_vertex(aircraft_t *shape)
{
    sfVector2f *vector_array = malloc(sizeof(sfVector2f) * 4);
    sfVector2f position = sfRectangleShape_getPosition(shape->hitbox);
    sfVector2f size = sfRectangleShape_getSize(shape->hitbox);
    float angle = sfRectangleShape_getRotation(shape->hitbox);

    vector_array[0] = rotate_point(position, position, angle);
    vector_array[1] = rotate_point((sfVector2f){position.x + size.x,
        position.y}, position, angle);
    vector_array[2] = rotate_point((sfVector2f){position.x + size.x,
        position.y + size.y}, position, angle);
    vector_array[3] = rotate_point((sfVector2f){position.x, position.y
        + size.y}, position, angle);
    return vector_array;
}

sfVector2f get_position_with_rotation(aircraft_t *aircraft, sfVector2f hitbox)
{
    return (sfVector2f){
        hitbox.x + (cos(aircraft->direction_angle * (180 / M_PI))
        - sin(aircraft->direction_angle) * (180 / M_PI)), hitbox.y
        + (cos(aircraft->direction_angle * (180 / M_PI))
        + sin(aircraft->direction_angle) * (180 / M_PI))
    };
}

static sfVector2f get_normalized_vector_with_coords(sfVector2f *point_list,
    sfVector2f position, int fisrt_index, int second_index)
{
    return get_normal_vector_left((sfVector2f){(point_list[fisrt_index].x
        + position.x) - (point_list[second_index].x + position.x),
        (point_list[fisrt_index].y + position.y)
        - (point_list[second_index].y + position.y)});
}

static sfVector2f *get_normals_list(sfVector2f *points_one,
    sfVector2f *points_two, sfVector2f pos_one, sfVector2f pos_two)
{
    sfVector2f *normals = malloc(sizeof(sfVector2f) * 8);

    normals[0] = get_normalized_vector_with_coords(points_one, pos_one, 1, 0);
    normals[1] = get_normalized_vector_with_coords(points_one, pos_one, 2, 1);
    normals[2] = get_normalized_vector_with_coords(points_one, pos_one, 3, 2);
    normals[3] = get_normalized_vector_with_coords(points_one, pos_one, 0, 3);
    normals[0] = get_normalized_vector_with_coords(points_two, pos_two, 1, 0);
    normals[1] = get_normalized_vector_with_coords(points_two, pos_two, 2, 1);
    normals[2] = get_normalized_vector_with_coords(points_two, pos_two, 3, 2);
    normals[3] = get_normalized_vector_with_coords(points_two, pos_two, 0, 3);
    return normals;
}

static bool determine_gap(float dot_product_one[], float dot_product_two[],
    sfVector2f *normals, sfVector2f *vectors[])
{
    float max_one;
    float min_one;
    float max_two;
    float min_two;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            dot_product_one[j] = dot_product_vector(normals[i], vectors[0][j]);
            dot_product_two[j] = dot_product_vector(normals[i], vectors[1][j]);
        }
        max_one = get_max_dot_product(dot_product_one, 4);
        min_one = get_min_dot_product(dot_product_one, 4);
        max_two = get_max_dot_product(dot_product_two, 4);
        min_two = get_min_dot_product(dot_product_two, 4);
        if ((max_one <= min_two) || (max_two <= min_one))
            return false;
    }
    return true;
}

bool separate_axis_theorem(aircraft_t *one, aircraft_t *two)
{
    sfVector2f hitbox_pos_one = sfRectangleShape_getPosition(one->hitbox);
    sfVector2f hitbox_pos_two = sfRectangleShape_getPosition(two->hitbox);
    sfVector2f *points_one = get_shape_vertex(one);
    sfVector2f *points_two = get_shape_vertex(two);
    sfVector2f pos_one = get_position_with_rotation(one, hitbox_pos_one);
    sfVector2f pos_two = get_position_with_rotation(two, hitbox_pos_two);
    sfVector2f *normals = get_normals_list(points_one, points_two,
        pos_one, pos_two);
    float dot_product_one[4];
    float dot_product_two[4];
    sfVector2f *vector[] = {points_one, points_two};
    bool is_a_collision = determine_gap(dot_product_one, dot_product_two,
        normals, vector);

    free(points_one);
    free(points_two);
    free(normals);
    return is_a_collision;
}
