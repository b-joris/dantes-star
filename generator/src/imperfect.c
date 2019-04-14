/*
** EPITECH PROJECT, 2019
** generator
** File description:
** imperfect
*/

#include <stdlib.h>
#include "generator.h"

static void fill_lasts(maze_t *maze)
{
    if (!(maze->height % 2)) {
        for (int i = 0; i < maze->height - 1; i++)
            maze->grid[i][maze->width - 1] = (rand() % 2) ? PATH : WALL;
    }
    if (!(maze->width % 2)) {
        for (int i = 0; i < maze->width - 1; i++)
            maze->grid[maze->height - 1][i] = (rand() % 2) ? PATH : WALL;
    }
}

int imperfect(maze_t *maze)
{
    int nb_loop = (maze->height + maze->width) / 20;

    generator(maze);
    maze->grid[maze->height - 1][maze->width - 1] = PATH;
    for (int i = 0; i < nb_loop; i++) {
        while (maze->grid[maze->y][maze->x] == PATH) {
            maze->x = rand() % (maze->width - 1) + 1;
            maze->x = (!(maze->x % 2)) ? maze->x - 1 : maze->x;
            maze->y = rand() % (maze->height - 1) + 1;
            maze->y = (!(maze->y % 2)) ? maze->y - 1 : maze->y;
        }
        maze->grid[maze->y][maze->x] = PATH;
    }
    fill_lasts(maze);
    if (maze->width > 1)
        maze->grid[0][1] = PATH;
    if (maze->height > 1)
        maze->grid[1][0] = PATH;
    return (0);
}