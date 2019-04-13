/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** window
*/

#include <stdlib.h>
#include <SFML/Graphics.h>

sfRenderWindow *create_window(unsigned int width, unsigned int height,
unsigned int framerate, char *name)
{
    sfVideoMode mode = {width, height, 32};
    sfRenderWindow *window = NULL;

    window = sfRenderWindow_create(mode, name, sfFullscreen, NULL);
    if (!window)
        return (NULL);
    sfRenderWindow_setFramerateLimit(window, framerate);
    return (window);
}