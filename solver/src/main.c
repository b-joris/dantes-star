/*
** EPITECH PROJECT, 2019
** Dante
** File description:
** main
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my_pointer.h"
#include "my_str.h"
#include "solver.h"

static int init_maze(maze_t *maze)
{
    maze->list = malloc(sizeof(list_t));

    if (!maze->list)
        return (84);
    maze->list = add_node_at_start(NULL, 0, 0);
    maze->height = count_height(maze->grid);
    if (maze->height == -1)
        return (84);
    maze->width = count_width(maze->grid);
    maze->x = 0;
    maze->y = 0;
    return (0);
}

static void free_maze(maze_t *maze)
{
    my_free(maze->grid);
    free_list(maze->list);
    my_free(maze);
}

static void replace_chars_solved(maze_t *maze)
{
    unsigned int size = strlen(maze->grid);

    for(unsigned int i = 0; i < size; i++)
        maze->grid[i] = (maze->grid[i] == '-') ? '*' : maze->grid[i];
    maze->grid[size - 1] = 'o';
}

static int maze_algo(maze_t *maze)
{
    if (init_maze(maze)) {
        free_maze(maze);
        return (my_puterror("Map Error\n"));
    }
    if (check_maze_errors(maze))
        return (my_puterror("Mappp Error\n"));
    if (maze->width == 0 || maze->height == 0) {
        free_maze(maze);
        return (my_puterror("Mapp error\n"));
    }
    if (solver(maze))
        printf("no solution found");
    else {
        replace_chars_solved(maze);
        printf("%s", maze->grid);
    }
    return (0);
}

int main(int ac, char **av)
{
    maze_t *maze = malloc(sizeof(maze_t));

    if (!maze)
        return (my_puterror("Malloc error\n"));
    if (ac != 2) {
        free(maze);
        return (my_puterror("Argument error\n"));
    }
    maze->grid = load_map(av[1]);
    if (!maze->grid) {
        free(maze);
        return (84);
    }
    return (maze_algo(maze));
}