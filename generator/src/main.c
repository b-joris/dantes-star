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

static void free_maze(maze_t *maze)
{
    my_free(maze->grid);
    my_free(maze);
}


static int set_maze(int ac, char **av, maze_t *maze)
{
    maze->perfect = (ac == 4) ? PERFECT : IMPERFECT;
    maze->width = atoi(av[1]);
    maze->height = atoi(av[2]);
    maze->grid = malloc(sizeof(char) * (maze->height * maze->width + maze->height + 1));
    if (!maze->grid)
        return (my_puterror("Malloc error\n"));
    memset(maze->grid, WALL, maze->height * maze->width + maze->height);
    for (int i = 0; i < maze->height; i++) {
        
    }
    maze->grid[maze->height * maze->width + maze->height] = '\0';
    return (0);
}

static void display_maze(maze_t *maze)
{
    write(1, maze->grid, strlen(maze->grid));
}

static int *check_paths(maze_t *maze, int (*x), int (*y), int (*possibilities))
{
    int  *paths = malloc(sizeof(int) * 4);

    (*possibilities) = 0;
    if (!paths)
        return (NULL);
    if ((*y) < maze->height - 2 && maze->grid[POS((*y) + 2, (*x), maze->width)] == WALL)
        paths[(*possibilities)++] = DOWN;
    if ((*y) > 1 && maze->grid[POS((*y) - 2, (*x), maze->width)] == WALL)
        paths[(*possibilities)++] = UP;
    if ((*x) > 1 && maze->grid[POS((*y), (*x) - 2, maze->width)] == WALL)
        paths[(*possibilities)++] = LEFT;
    if ((*x) < maze->width - 2 && maze->grid[POS((*y), (*x) + 2, maze->width)] == WALL)
        paths[(*possibilities)++] = RIGHT;
    return (paths);
}

static int generator(maze_t *maze, int x, int y)
{
    int direction = 0;
    int possibilities = 0;
    int *paths = NULL;
    list_t *list = add_node_at_start(NULL, x, y);

    if (!list)
        return (84);
    while (list) {
        printf("%s\n", maze->grid);
        usleep(200000);
        maze->grid[POS(y, x, maze->width)] = PATH;
        paths = check_paths(maze, &x, &y, &possibilities);
        if (!possibilities) {
            list = remove_node_at_start(list);
            if (list) {
                x = list->x;
                y = list->y;
            }
            continue;
        }
        direction = paths[(rand() % possibilities)];
        if (direction == DOWN) {
            maze->grid[POS(y + 1, x, maze->width)] = PATH;
            y += 2;
        }
        else if (direction == UP) {
            maze->grid[POS(y - 1, x, maze->width)] = PATH;
            y -= 2;
        }
        else if (direction == RIGHT) {
            maze->grid[POS(y, x + 1, maze->width)] = PATH;
            x += 2;
        }
        else if (direction == LEFT) {
            maze->grid[POS(y, x - 1, maze->width)] = PATH;
            x -= 2;
        }
        list = add_node_at_start(list, x, y);
    }
    my_free(paths);
    return (0);
}

int main(int ac, char **av)
{
    maze_t *maze = malloc(sizeof(maze_t));
    int x_start = 0;
    int y_start = 0;

    srand(time(NULL));
    if (!maze)
        return (0);
    if (error_handling(ac, av))
        return (84);
    if (set_maze(ac, av, maze))
        return (0);
    //generator(maze, x_start, y_start);
    //maze->grid[POS(maze->height - 1, maze->width - 1, maze->width)] = PATH;
    //xmaze->grid[POS(maze->height - 2, maze->width - 2, maze->width)] = PATH;
    display_maze(maze);
    free_maze(maze);
    return (0);
}

