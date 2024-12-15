/*
** EPITECH PROJECT, 2024
** my_strnum.c
** File description:
** task07
*/

#include "my_lib.h"
#include <stdlib.h>

int compute(int nb, char *buffer, int counter_digits, int divider)
{
    int i = 0;

    if (the_small_int(nb) == 0) {
        while (divider <= (nb / 10)) {
            counter_digits += 1;
            divider *= 10;
        }
        while (counter_digits > 0) {
            buffer[i] = nb / divider + 48;
            i++;
            nb %= divider;
            counter_digits -= 1;
            divider /= 10;
        }
    }
    return i;
}

char *my_strnum(int nb)
{
    int divider = 1;
    int counter_digits = 1;
    char *buffer = malloc(sizeof(char) * 500);
    int test = compute(nb, buffer, counter_digits, divider);

    buffer[test] = '\0';
    return buffer;
}
