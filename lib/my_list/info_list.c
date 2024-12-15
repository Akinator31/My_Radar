/*
** EPITECH PROJECT, 2024
** B-PSU-100-TLS-1-1-myls-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** info_list
*/

#include <stdlib.h>
#include "../../include/my_list.h"
#include "my_lib.h"

linked_list_t *new_list(void)
{
    return NULL;
}

linked_list_t *clear_list(linked_list_t *list, void (*clear_func)(void *data))
{
    linked_list_t *temp = list;

    while (list != NULL) {
        temp = list;
        list = list->next;
        clear_func(temp->data);
        free(temp);
    }
    free(list);
    return NULL;
}
