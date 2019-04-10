/*
** EPITECH PROJECT, 2019
** Dante
** File description:
** generator
*/

#ifndef GENERATOR_H_
#define GENERATOR_H_

#define WALL 'X'
#define PATH '*'
#define POS(Y, X, WIDTH) ((Y * (WIDTH + 1)) + X)

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
    char **grid;

} maze_t;

#endif /* !GENERATOR_H_ */
