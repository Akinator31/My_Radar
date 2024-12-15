/*
** EPITECH PROJECT, 2024
** B-PSU-100-TLS-1-1-myls-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** add_data
*/

#include <stdlib.h>
#include <sys/stat.h>
#include "../../include/my_list.h"
#include "my_lib.h"
#include <stdarg.h>

linked_list_t *push_front_list(linked_list_t *list, void *data)
{
    linked_list_t *new_element = malloc(sizeof(linked_list_t));

    if (data == NULL)
        return NULL;
    new_element->data = data;
    new_element->next = list;
    return new_element;
}

linked_list_t *push_front_list_all(linked_list_t *list, int nb, ...)
{
    va_list args;

    va_start(args, nb);
    for (int i = 0; i < nb; i++) {
        list = push_front_list(list, va_arg(args, void *));
    }
    va_end(args);
    return list;
}

linked_list_t *push_back_list(linked_list_t *list, void *data)
{
    linked_list_t *new_element = malloc(sizeof(linked_list_t));
    linked_list_t *temp = list;
    linked_list_t *prev;

    if (list == NULL) {
        new_element->data = data;
        new_element->next = NULL;
        return new_element;
    }
    while (temp != NULL) {
        prev = temp;
        temp = temp->next;
    }
    new_element->data = data;
    new_element->next = NULL;
    prev->next = new_element;
    return list;
}

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *prev = NULL;
    linked_list_t *curr = *begin;
    linked_list_t *next = NULL;

    while (curr->next != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *begin = next;
    curr->next = prev;
}
