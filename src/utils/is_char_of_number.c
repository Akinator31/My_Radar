/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** is_char_of_number
*/

int is_a_number(char actual_char)
{
    if ((actual_char >= '0') && (actual_char <= '9'))
        return 1;
    return 0;
}

int is_char_of_number(char *buffer)
{
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (!is_a_number(buffer[i]))
            return 0;
    }
    return 1;
}
