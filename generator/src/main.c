/*
** EPITECH PROJECT, 2019
** Dante
** File description:
** main
*/

#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_str.h"
#include "my_list.h"
#include "my_pointer.h"
#include "generator.h"

static int error_handling(int ac, char **av)
{
    if (ac < 3 || ac > 4)
        return (my_puterror("Argument error\n"));
    if (atoi(av[1]) <= 0 || atoi(av[2]) <= 0)
        return (my_puterror("Number is is null or under 0\n"));
    return (0);
}

static void display_maze(maze_t *maze)
{
    for (int i = 0; i < maze->height; i++) {
        write(1, maze->grid[i], maze->width);
        if (i != maze->height - 1)
            write(1, "\n", 1);
    }
}

static void free_maze(maze_t *maze)
{
    for (int i = 0; i < maze->height; i++)
        free(maze->grid[i]);
    free(maze->grid);
    free(maze);
}

int main(int ac, char **av)
{
    maze_t *maze = malloc(sizeof(maze_t));

    srand(time(NULL));
    if (!maze)
        return (0);
    if (error_handling(ac, av)) {
        my_free(maze);
        return (84);
    }
    if (set_maze(ac, av, maze))
        return (0);
    maze->perfect ? perfect(maze) : imperfect(maze);
    maze->grid[maze->height - 1][maze->width - 2] = PATH;
    maze->grid[maze->height - 1][maze->width - 1] = PATH;
    display_maze(maze);
    free_maze(maze);
    return (0);
}