/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myradar-pavel.de-wavrechin
** File description:
** errors
*/

#ifndef INCLUDED_ERRORS_H
    #define INCLUDED_ERRORS_H

typedef int (*error_func_t)(void);

typedef enum error_s {
    NOT_ENOUGHT_ARG,
    TOO_MANY_ARG,
    INVALID_SCRIPT_FILE,
    INVALID_SCRIPT_CONTENT,
} error_t;

int errors_manager(error_t error_type);
int not_enought_argument(void);
int too_many_argument(void);
int invalid_script_file(void);
int invalid_script_content(void);


#endif
