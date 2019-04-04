/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** sprites
*/

#include <SFML/Graphics.h>
#include "my_csfml.h"

sprite_t *create_sprite(char *path, int id, int x, int y)
{
    sprite_t *sprite = malloc(sizeof(sprite));

    if (!sprite)
        return (NULL);
    sprite->sprite = sfSprite_create();
    sprite->texture = sfTexture_createFromFile(path, NULL);
    if (!sprite->texture)
        return (NULL);
    sprite->pos->top = y;
    sprite->pos->left = x;
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    return (sprite);
}

void destroy_sprite(sprite_t *sprite)
{
    if (sprite->texture)
        sfTexture_destroy(sprite->texture);
    if (sprite->sprite)
        sfSprite_destroy(sprite->sprite);
    my_free(sprite);
}