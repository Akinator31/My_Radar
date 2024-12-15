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
void clear_list(linked_list_t *list);

#endif
