/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** errors_manager
*/

#include <unistd.h>
#include "errors.h"

static const error_func errors[] = {
    &not_enought_argument,
    &too_many_argument,
    &invalid_script_file,
    &invalid_script_content,
};

int errors_manager(error_t error_type)
{
    return (*errors[error_type])();
}
