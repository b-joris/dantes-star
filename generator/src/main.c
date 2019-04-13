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
    if (ac < 2 || ac > 4)
        return (my_puterror("Argument error\n"));
    else if (my_isnum(av[1]) || my_isnum(av[2]))
        return (my_puterror("Argument is not a number\n"));
    if (atoi(av[1]) <= 0 || atoi(av[2]) <= 0)
        return (my_puterror("Number is is null or under 0\n"));
    return (0);
}

static int set_maze(int ac, char **av, maze_t *maze)
{
    maze->perfect = (ac == 4) ? PERFECT : IMPERFECT;
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
    return (0);
}

static void display_maze(maze_t *maze)
{
    for (int i = 0; i < maze->height; i++) {
        write(1, maze->grid[i], maze->height);
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
    if (error_handling(ac, av))
        return (84);
    if (set_maze(ac, av, maze))
        return (0);
    maze->perfect ? perfect(maze) : imperfect(maze);
    display_maze(maze);
    free_maze(maze);
    return (0);
}