/*
** EPITECH PROJECT, 2024
** my_strcmp.c
** File description:
** task06
*/

#include <stdlib.h>
#include "my_lib.h"

char is_alpha(char act_char)
{
    if ((act_char >= 'A') && (act_char <= 'Z'))
        return act_char + 32;
    return act_char;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    int result = 0;
    char *test1 = my_strlowcase(s1);
    char *test2 = my_strlowcase(s2);

    for (int i = 0; (test1[i] != '\0') || (test2[i] != '\0'); i++) {
        if (test1[i] != test2[i]) {
            result = test1[i] - test2[i];
            return result;
        }
    }
    result = test1[i] != test2[i];
    return result;
}
