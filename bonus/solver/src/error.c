/*
** EPITECH PROJECT, 2019
** CPE_dante_2018
** File description:
** error
*/

#include "solver.h"

int check_maze_errors(maze_t *maze)
{
    unsigned int standard_size = 0;
    unsigned int line_size = 0;

    for (; (maze->grid && maze->grid[standard_size]) &&
    maze->grid[standard_size] != '\n'; standard_size++);
    for (int i = 0; i < ((maze->height + 1) * maze->width) - 1; i++) {
        if ((maze->grid[i] != 'X' && maze->grid[i] != '*')
        && (maze->grid[i] != '\n' && maze->grid[i] != '\0'))
            return (84);
    }
    return (0);
}