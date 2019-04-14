/*
** EPITECH PROJECT, 2019
** CPE_dante_2018
** File description:
** solver
*/

#include <stdlib.h>
#include "my_pointer.h"
#include "solver.h"

static int check_possibilities(maze_t *maze, int possibilities)
{
    if (!possibilities) {
        maze->grid[POS(maze->y, maze->x, maze->width)] = PASSED;
        maze->list = remove_node_at_start(maze->list);
        if (maze->list) {
            maze->x = maze->list->x;
            maze->y = maze->list->y;
        }
        return (0);
    }
    return (1);
}

static int *check_paths(maze_t *maze, int (*possibilities))
{
    int  *paths = malloc(sizeof(int) * 4);
    int x = maze->x;
    int y = maze->y;
    int width = maze->width;
    int height = maze->height;

    (*possibilities) = 0;
    if (y > 0 && maze->grid[POS((y - 1), x,width)] == PATH)
        paths[(*possibilities)++] = UP;
    if ((y < (height - 1)) && maze->grid[POS((y + 1), x, width)] == PATH)
        paths[(*possibilities)++] = DOWN;
    if ((x < (width - 1)) && maze->grid[POS(y, (x + 1), width)] == PATH)
        paths[(*possibilities)++] = RIGHT;
    if (x > 0 && maze->grid[POS(y, (x - 1), width)] == PATH)
        paths[(*possibilities)++] = LEFT;
    return (paths);
}

static void deplacement(maze_t *maze, int direction)
{
    if (direction == UP)
        maze->y -= 1;
    if (direction == DOWN)
        maze->y += 1;
    if (direction == RIGHT)
        maze->x += 1;
    if (direction == LEFT)
        maze->x -= 1;
    maze->list = add_node_at_start(maze->list, maze->x, maze->y);
}

int solver(maze_t *maze)
{
    int *paths = NULL;
    int possibilities = 0;
    int direction = 0;
    int width_max = maze->width - 1;
    int height_max = maze->height - 1;

    while (maze->list && (maze->x != width_max || maze->y != height_max)) {
        maze->grid[POS(maze->y, maze->x, maze->width)] = PASS;
        paths = check_paths(maze, &possibilities);
        if (check_possibilities(maze, possibilities)) {
            direction = paths[(rand() % possibilities)];
            deplacement(maze, direction);
            my_free(paths);
        }
    }
    if (maze->list)
        return (0);
    return (1);
}