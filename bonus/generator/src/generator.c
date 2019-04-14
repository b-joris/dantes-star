/*
** EPITECH PROJECT, 2019
** generator
** File description:
** generator
*/

#include <ncurses.h>
#include <stdlib.h>
#include "my_list.h"
#include "my_pointer.h"
#include "generator.h"

static int *check_paths(maze_t *maze, int (*possibilities))
{
    int  *paths = malloc(sizeof(int) * 4);

    (*possibilities) = 0;
    if (!paths)
        return (NULL);
    if (maze->y < maze->height - 2 && maze->grid[maze->y + 2][maze->x] == WALL)
        paths[(*possibilities)++] = DOWN;
    if (maze->y > 1 && maze->grid[maze->y - 2][maze->x] == WALL)
        paths[(*possibilities)++] = UP;
    if (maze->x > 1 && maze->grid[maze->y][maze->x - 2] == WALL)
        paths[(*possibilities)++] = LEFT;
    if (maze->x < maze->width - 2 && maze->grid[maze->y][maze->x + 2] == WALL)
        paths[(*possibilities)++] = RIGHT;
    return (paths);
}

static int check_possibilities(maze_t *maze, int possibilities)
{
    if (!possibilities) {
        maze->list = remove_node_at_start(maze->list);
        if (maze->list) {
            maze->x = maze->list->x;
            maze->y = maze->list->y;
        }
        return (0);
    }
    return (1);
}

static void break_walls(maze_t *maze, int direction)
{
    if (direction == DOWN) {
        maze->grid[maze->y + 1][maze->x] = PATH;
        maze->y += 2;
    }
    if (direction == UP) {
        maze->grid[maze->y - 1][maze->x] = PATH;
        maze->y -= 2;
    }
    if (direction == RIGHT) {
        maze->grid[maze->y][maze->x + 1] = PATH;
        maze->x += 2;
    }
    if (direction == LEFT) {
        maze->grid[maze->y][maze->x - 1] = PATH;
        maze->x -= 2;
    }
    maze->list = add_node_at_start(maze->list, maze->x, maze->y);
}

int generator(maze_t *maze)
{
    int direction = 0;
    int possibilities = 0;
    int *paths = NULL;

    initscr();
    start_color();
    init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(PATH, COLOR_BLUE, COLOR_BLUE);
    while (maze->list) {
        clear();
        display_maze(maze);
        maze->grid[maze->y][maze->x] = PATH;
        paths = check_paths(maze, &possibilities);
        if (check_possibilities(maze, possibilities)) {
            direction = paths[(rand() % possibilities)];
            break_walls(maze, direction);
            my_free(paths);
        }
    }
    free_list(maze->list);
    return (0);
}