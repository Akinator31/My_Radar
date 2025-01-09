/*
** EPITECH PROJECT, 2024
** mylist.h
** File description:
** header file for linked list structure
*/

#ifndef MYLIST_H
    #define MYLIST_H
    #include <dirent.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include "my_list.h"

typedef struct linked_list_s linked_list_t;

struct linked_list_s {
    linked_list_t *next;
    void *data;
};

linked_list_t *new_list(void);
linked_list_t *push_front_list(linked_list_t *list, void *data);
linked_list_t *push_front_list_all(linked_list_t *list, int nb, ...);
linked_list_t *pop_front_list(linked_list_t *list,
    void (*clean_func)(void *data));
linked_list_t *push_back_list(linked_list_t *list, void *data);
linked_list_t *clear_list_and_data(linked_list_t *list,
    void (*clear_func)(void *data));
linked_list_t *clear_list(linked_list_t *list);
linked_list_t *delete_node(linked_list_t **list, linked_list_t *element);
int get_linked_list_len(linked_list_t *list);
linked_list_t *push_back_list_all(linked_list_t *list, int nb, ...);
int get_number_of_plane(linked_list_t *list);

#endif
