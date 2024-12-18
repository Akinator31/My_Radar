/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** entity_manager
*/

#include <stdlib.h>
#include "structure.h"
#include "entity.h"
#include "my_list.h"
#include "utils.h"

linked_list_t *load_aircrafts(engine_t *engine,
    linked_list_t *list, char **lines_element)
{
    entity_t *aircraft = NULL;

    aircraft = create_aircraft_entity(GET_RES(AIRCRAFT)->ressource,
        SF_VECTOR_2F(my_getnbr(lines_element[1]),
        my_getnbr(lines_element[2])), SF_VECTOR_2F(
        my_getnbr(lines_element[3]), my_getnbr(lines_element[4])));
    ((aircraft_t *)(aircraft->data))->velocity = my_getnbr(lines_element[5]);
    ((aircraft_t *)(aircraft->data))->offset_takeoff =
        my_getnbr(lines_element[6]);
    list = push_back_list(list, aircraft);
    return list;
}

linked_list_t *load_tower(engine_t *engine,
    linked_list_t *list, char **lines_element)
{
    list = push_back_list(list,
        create_tower_entity(GET_RES(CONTROL_TOWER)->ressource,
    SF_VECTOR_2F(my_getnbr(lines_element[1]),
        my_getnbr(lines_element[2])), my_getnbr(lines_element[3])));
    return list;
}

linked_list_t *load_entities(linked_list_t *entity_list, engine_t *engine)
{
    char *lines = NULL;
    char **lines_element = NULL;
    size_t len = 0;
    FILE *file = fopen(engine->script_path, "r");

    while (getline(&lines, &len, file) != -1) {
        lines_element = my_str_to_word_array(lines);
        if (my_strcmp(lines_element[0], "A") == 0)
            entity_list = load_aircrafts(engine, entity_list, lines_element);
        if (my_strcmp(lines_element[0], "T") == 0)
            entity_list = load_tower(engine, entity_list, lines_element);
        free_2d_array_of_char(lines_element);
    }
    free(lines);
    fclose(file);
    return entity_list;
}
