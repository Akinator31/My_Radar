/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin [WSL : Ubuntu]
** File description:
** my_hunter
*/

#ifndef INCLUDED_MY_HUNTER_H
    #define INCLUDED_MY_HUNTER_H
    #include <SFML/Graphics.h>
    #define WIDTH 1920
    #define HEIGTH 1080
    #define NAME "MY RADAR"

sfRenderWindow *create_window(unsigned int width,
    unsigned int heigth, char *window_title);

#endif
