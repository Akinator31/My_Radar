/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** help_display
*/

#include <unistd.h>
#include "structure.h"
#include "my_lib.h"
#include "utils.h"
#include "errors.h"

static const char *help_message = "=============================\n"
    "        MY RADAR GAME        \n"
    "=============================\n"
    "\n"
    "DESCRIPTION:\n"
    "  My Radar is an air traffic visualization panel. The goal is to "
    "simulate\n  and manage aircrafts and control towers according to the "
    "rules defined\n  in the provided script file.\n"
    "\n"
    "USAGE:\n"
    "  ./my_radar [OPTIONS] path_to_script\n"
    "\n"
    "  path_to_script : The path to the script file containing the "
    "simulation\n                   details.\n"
    "\n"
    "OPTIONS:\n"
    "  -h          Display this help message and exit.\n"
    "\n"
    "USER INTERACTIONS:\n"
    "  'L' key     Enable/disable hitboxes and control areas.\n"
    "  'S' key     Enable/disable entity sprites.\n"
    "\n"
    "GOOD LUCK!\n";

int help(int ac, char **av)
{
    if (ac > 2)
        return errors_manager(TOO_MANY_ARG);
    if (my_strcmp(av[1], "-h") == 0)
        write(1, help_message, my_strlen(help_message) + 1);
    return 0;
}
