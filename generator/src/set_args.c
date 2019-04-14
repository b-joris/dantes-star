/*
** EPITECH PROJECT, 2019
** CPE_dante_2018
** File description:
** set_args
*/

#include <stdlib.h>
#include <string.h>
#include "my_pointer.h"
#include "my_str.h"
#include "generator.h"

static int set_perfect(int ac, char **av, maze_t * maze)
{
    if (ac == 3) {
        maze->perfect = IMPERFECT;
        return (0);
    }
    if (ac == 4 && (strcmp("perfect", av[3]) == 0)) {
        maze->perfect = PERFECT;
        return (0);
    }
    else if (ac == 4 && (strcmp("imperfect", av[3]) == 0)) {
        maze->perfect = IMPERFECT;
        return (0);
    }
    return (my_puterror("Argument error\n"));
}

int set_maze(int ac, char **av, maze_t *maze)
{
    maze->width = atoi(av[1]);
    maze->height = atoi(av[2]);
    maze->x = 0;
    maze->y = 0;
    maze->list = add_node_at_start(NULL, 0, 0);
    maze->grid = malloc(sizeof(char *) * (maze->height + 1));
    if (!maze->grid || !maze->list)
        return (84);
    maze->grid[maze->height] = NULL;
    if (!maze->grid)
        return (my_puterror("Malloc error\n"));
    for (int i = 0; i < maze->height; i++) {
        maze->grid[i] = malloc(sizeof(char) * (maze->width + 1));
        memset(maze->grid[i], WALL, maze->width);
        maze->grid[i][maze->width] = '\0';
    }
     return (set_perfect(ac, av, maze));
}