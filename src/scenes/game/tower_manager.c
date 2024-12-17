/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** tower_manager
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"
#include "entity.h"
#include "utils.h"
#include "my_lib.h"

linked_list_t *create_tower(linked_list_t *entity_list, engine_t *engine)
{
    char *lines = NULL;
    char **lines_element = NULL;
    size_t len = 0;
    FILE *file = fopen(engine->script_path, "r");

    while (getline(&lines, &len, file) != -1) {
        lines_element = my_str_to_word_array(lines);
        if (my_strcmp(lines_element[0], "T") == 0) {
            entity_list = push_back_list(entity_list, create_tower_entity(get_ressource_by_id(engine->ressources,
                TOWER)->ressource, SF_VECTOR_2F(my_getnbr(lines_element[1]),
                my_getnbr(lines_element[2]))));
        }
        free_2d_array_of_char(lines_element);
    }
    free(lines);
    fclose(file);
    return entity_list;
}