/*
** EPITECH PROJECT, 2019
** Dante
** File description:
** solver.h
*/

#ifndef _SOLVER_H
#define _SOLVER_H

#include "my_list.h"

#define WALL 'X'
#define PATH '*'
#define PASS 'o'
#define PASSED '-'
#define POS(Y, X, WIDTH) ((Y * (WIDTH + 1)) + X)

enum {
    UP = 1,
    RIGHT = 2,
    LEFT = 3,
    DOWN = 4
};

typedef struct s_maze {
    int x;
    int y;
    int width;
    int height;
    char *grid;
    list_t *list;
} maze_t;

int solver(maze_t *maze);
int check_maze_errors(maze_t *maze);
int count_width(char *map);
int count_height(char *map);
char *load_map(char *path);
void display_maze(maze_t *maze);

#endif
