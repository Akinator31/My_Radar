/*
** EPITECH PROJECT, 2024
** B-MUL-100-TLS-1-1-myhunter-pavel.de-wavrechin
** File description:
** set_sprite_hover
*/

#include "structure.h"
#include "engine.h"

void set_sprite_hover(sfSprite *sprite, engine_t *engine,
    sfTexture *new_texture, sfTexture *original_texture)
{
    sfFloatRect texture_rect = sfSprite_getGlobalBounds(sprite);
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(engine->window);
    sfVector2f window_size = {sfRenderWindow_getSize(engine->window).x,
        sfRenderWindow_getSize(engine->window).y};

    if (sfFloatRect_contains(&texture_rect, mouse_pos.x *
        (1920 / window_size.x), mouse_pos.y * (1080 / window_size.y))) {
        sfSprite_setTexture(sprite, new_texture, sfTrue);
    } else {
        sfSprite_setTexture(sprite, original_texture, sfTrue);
    }
}
