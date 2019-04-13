/*
** EPITECH PROJECT, 2019
** generator
** File description:
** perfect
*/

#include "generator.h"

int perfect(maze_t *maze)
{
    generator(maze);
    if (!(maze->height % 2)) {
        for (int i = 2; i < maze->width; i++)
            (maze->grid[maze->height - 2][i] == PATH &&
            maze->grid[maze->height - 1][i - 1] != PATH) ?
            maze->grid[maze->height - 1][i] = PATH : WALL;
    }
    if (!(maze->width % 2)) {
        for (int i = 2; i < maze->height; i++)
            (maze->grid[i][maze->width - 2] == PATH &&
            maze->grid[i - 1][maze->width - 1] != PATH) ?
            maze->grid[i][maze->height - 1] = PATH : WALL;
    }
    maze->grid[maze->height - 2][maze->width - 1] = WALL;
    maze->grid[maze->height - 1][maze->width - 1] = PATH;
    return (0);
}