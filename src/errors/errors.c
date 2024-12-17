/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** errors
*/

#include <unistd.h>

int not_enought_argument(void)
{
    write(2, "Not enought arguments was given to the program\n", 48);
    return 84;
}

int too_many_argument(void)
{
    write(2, "Too many argument was given to the program\n", 44);
    return 84;
}

int invalid_script_file(void)
{
    write(2, "Invalid script file\n", 21);
    return 84;
}

int invalid_script_content(void)
{
    write(2, "Invalid script content\n", 24);
    return 84;
}
