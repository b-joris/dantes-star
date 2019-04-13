/*
** EPITECH PROJECT, 2019
** Lib CSFML
** File description:
** my_csfml
*/

#ifndef MY_CSFML_H_
#define MY_CSFML_H_

#include <SFML/Graphics.h>

typedef struct s_sprite {
    int id;
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect *pos;
    sfIntRect *anim;
    sfVector2f *speed;
} sprite_t;

sfRenderWindow *create_window(unsigned int width, unsigned int height,
unsigned int framerate, char *name);

#endif /* !MY_CSFML_H_ */
