/*
** EPITECH PROJECT, 2024
** B-PSU-100-TLS-1-1-myls-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** remove_data
*/

#include <stdlib.h>
#include "my_list.h"
#include "my_lib.h"

linked_list_t *pop_front_list(linked_list_t *list,
    void (*clean_func)(void *data))
{
    linked_list_t *temp;

    if (list == NULL) {
        return list;
    }
    if (list->next == NULL) {
        clean_func(list);
        list = NULL;
        return list;
    }
    temp = list->next;
    clean_func(list);
    return temp;
}

linked_list_t *delete_node(linked_list_t **list, linked_list_t *element)
{
    linked_list_t *temp = NULL;
    linked_list_t *prev = NULL;

    if ((list == NULL) || (*list == NULL) || (element == NULL))
        return element;
    if (*list == element) {
        temp = *list;
        *list = (*list)->next;
        free(temp);
        return *list;
    }
    prev = *list;
    while ((prev->next != NULL) && (prev->next != element))
        prev = prev->next;
    if (prev->next == NULL)
        return NULL;
    prev->next = element->next;
    free(element);
    return prev->next;
}
