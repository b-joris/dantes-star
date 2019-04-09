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
#include "my_pointer.h"
#include "generator.h"

int explored = 0;

int error_handling(int ac, char **av)
{
    if (ac < 2 || ac > 4)
        return (my_puterror("Argument error\n"));
    else if (my_isnum(av[1]) || my_isnum(av[2]))
        return (my_puterror("Argument is not a number\n"));
    if (atoi(av[1]) <= 0 || atoi(av[2]) <= 0)
        return (my_puterror("Number is is null or under 0\n"));
    return (0);
}

int set_maze(int ac, char **av, maze_t *maze)
{
    maze->perfect = (ac == 4) ? PERFECT : IMPERFECT;
    maze->width = atoi(av[1]);
    maze->height = atoi(av[2]);
    maze->grid = malloc(sizeof(char *) * (maze->height + 1));
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

int *check_paths(maze_t *maze, int x, int y, int (*possibilities))
{
    int  *paths = malloc(sizeof(int) * 4);

    if (!paths)
        return (NULL);
    if (y < maze->height - 2 && maze->grid[y + 2][x] == WALL)
        paths[(*possibilities)++] = DOWN;
    if (y > 1 && maze->grid[y - 2][x] == WALL)
        paths[(*possibilities)++] = UP;
    if (x > 1 && maze->grid[y][x - 2] == WALL)
        paths[(*possibilities)++] = LEFT;
    if (x < maze->width - 2 && maze->grid[y][x + 2] == WALL)
        paths[(*possibilities)++] = RIGHT;
    paths[(*possibilities)] = NULL;
    return (paths);
}

void free_maze(maze_t *maze)
{
    for (int i = 0; i < maze->height; i++)
        my_free(maze->grid[i]);
    my_free(maze->grid);
}

int generator(maze_t *maze, int x, int y)
{
    int *paths = NULL;
    int direction = 0;
    int possibilities = 0;

    maze->grid[y][x] = PATH;
    while(explored < maze->height * maze->width) {
        paths = check_paths(maze, x, y, &possibilities);
        if (!paths)
            return (my_puterror("Malloc error\n"));
        if (possibilities) {
            direction = paths[(rand() % possibilities)];
            if (direction == DOWN) {
                ++explored;
                maze->grid[y + 1][x] = PATH;
                generator(maze, x, y + 2);
            }
            if (direction == UP) {
                ++explored;
                maze->grid[y - 1][x] = PATH;
                generator(maze, x, y - 2);
            }
            if (direction == LEFT) {
                ++explored;
                maze->grid[y][x - 1] = PATH;
                generator(maze, x - 2, y);
            }
            if (direction == RIGHT) {
                ++explored;
                maze->grid[y][x + 1] = PATH;
                generator(maze, x + 2, y);
            }
            possibilities = 0;
            free(paths);
        }
        else
            break;
    }
    return (0);
}

int main(int ac, char **av)
{
    maze_t *maze = malloc(sizeof(maze_t));
    int poss = 0;
    int *paths = NULL;

    srand(time(NULL));
    if (!maze)
        return (0);
    if (error_handling(ac, av))
        return (84);
    if (set_maze(ac, av, maze))
        return (0);
    generator(maze, 0, 0);
    free_maze(maze);
    return (0);
}
