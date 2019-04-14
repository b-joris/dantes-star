/*
** EPITECH PROJECT, 2019
** Dante
** File description:
** generator
*/

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "my_list.h"

#define WALL 'X'
#define PATH '*'

enum {
    IMPERFECT = 0,
    PERFECT = 1
};

enum {
    UP = 1,
    RIGHT = 2,
    LEFT = 3,
    DOWN = 4
};

typedef struct s_maze {
    int width;
    int height;
    int perfect;
    int x;
    int y;
    char **grid;
    list_t *list;

} maze_t;

int generator(maze_t *maze);
int perfect(maze_t *maze);
int imperfect(maze_t *maze);
int set_maze(int ac, char **av, maze_t *maze);
void display_maze(maze_t *maze);

#endif /* !GENERATOR_H_ */
