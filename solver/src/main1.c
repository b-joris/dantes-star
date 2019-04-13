/*
** EPITECH PROJECT, 2019
** Dante
** File description:
** main
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"
//#define POS(Y, X, WIDTH) ((Y * (WIDTH + 1)) + X)
//#define POS(Y, X, WIDTH) ((X * (Y - 1)) + Y)

//#ifndef _MAZE_H
//#define _MAZE_H

typedef struct maze {
    char *map;
    int *lab;
    int len_one_line;
    int nbr_of_char;
} maze;

void put_into_map(struct maze *maze, char *folder)
{
    maze->map = NULL;
    struct stat st;
    int fd = open(folder, O_RDONLY);

    stat(folder, &st);
    maze->map = malloc(sizeof(char) * (st.st_size + 1));
    if (!maze->map)
        return;
    if (read(fd, maze->map, st.st_size) <= 0)
        return;
    maze->nbr_of_char = st.st_size;
//    maze->map[0] = '0';
//    maze->map[maze->nbr_of_char - 2] = 'E';
}

void set_struct_maze(struct maze *maze)
{
    for (maze->len_one_line = 0; maze->map[maze->len_one_line] != '\n'; maze->len_one_line++);
    maze->lab = malloc(sizeof(int) * (maze->nbr_of_char + 1));
    for (int i = 0; maze->map[i]; i++) {
        if (maze->map[i] == '*')
            maze->lab[i] = -2;
        if (maze->map[i] == 'X')
            maze->lab[i] = -3;
        if (maze->map[i] == '\n')
            maze->lab[i] = -4;
    }
    maze->lab[maze->nbr_of_char - 2] = -1;
    maze->lab[0] = 0;
/*    for (int i = 0; i != maze->nbr_of_char; i++) {
        printf("%c", 41 + maze->lab[i]);
        if (maze->lab[i] == -4)
            printf("\n");
    } */
}

void basic_check(struct maze *maze, int i, int count)
{
    if (maze->lab[i + 1] == -2)
        maze->lab[i + 1] = count;
    if (maze->lab[i - 1] == -2)
        maze->lab[i - 1] = count;
}

void check_side(struct maze *maze, int i, int count)
{
    if (i == 0) {
        if (maze->lab[i + 1] == -2)
            maze->lab[i + 1] = count;
        if (maze->lab[i + maze->len_one_line + 1] == -2)
            maze->lab[i + maze->len_one_line + 1] = count;
    }
    if (i == (maze->nbr_of_char - 1)) {
        if (maze->lab[i - 1] == -2)
            maze->lab[i - 1] = count;
        if (maze->lab[i - maze->len_one_line - 1] == -2)
            maze->lab[i - maze->len_one_line - 1] = count;
    }
    if (i > 0 && i < 11 && maze->lab[i] != -3) {
        basic_check(maze, i, count);
        if (maze->lab[i + maze->len_one_line + 1] == -2)
            maze->lab[i + maze->len_one_line + 1] = count;
    }
    if (i > (maze->nbr_of_char - 11) && i < (maze->nbr_of_char - 2)) {
        basic_check(maze, i, count);
        if (maze->lab[i - maze->len_one_line - 1] == -2)
            maze->lab[i - maze->len_one_line - 1] = count;
    }
    if (i > 10 && i < maze->nbr_of_char - 11) {
        basic_check(maze, i, count);
        if (maze->lab[i - maze->len_one_line - 1] == -2)
            maze->lab[i - maze->len_one_line - 1] = count;
        if (maze->lab[i + maze->len_one_line + 1] == -2)
            maze->lab[i + maze->len_one_line + 1] = count;
   }
}

char *int_s_to_char_s(struct maze *maze)
{
    char *map = malloc(sizeof(char) * (maze->nbr_of_char + 1));

    for (int i = 0; i != maze->nbr_of_char; i++) {
            if (maze->lab[i] == -4)
                map[i] = '\n';
            if (maze->lab[i] == -3)
                map[i] = 'X';
            if (maze->lab[i] == -2)
                map[i] = '*';
            if (maze->lab[i] > -2)
                map[i] = 'o';
        }
        printf("%s\n", map);
        write(1, "\n", 1);
        return (map);
}

void find_way(struct maze *maze)
{
    int count = 0;

    for (; maze->lab[maze->nbr_of_char - 3] < 0 && maze->lab[maze->nbr_of_char - maze->len_one_line - 3] < 0 ; count++) {
        for (int i = 0; i != maze->nbr_of_char; i++) {
            printf("banana\n");
            if (maze->lab[i] == count)
                check_side(maze, i, count + 1);
        }
         printf("+");
        for (int i = 0; i != maze->nbr_of_char; i++) {
            if (maze->lab[i] > 0)
                printf("+");
            printf("%i", maze->lab[i]);
            if (maze->lab[i] == -4)
                printf("\n");
        } 
    }
}

void my_free(struct maze *maze)
{
    free(maze->map);
    free(maze->lab);
    free(maze);
}

int main(int ac, char **av)
{
    struct maze *maze = malloc(sizeof(struct maze));

    put_into_map(maze, av[1]);
    set_struct_maze(maze);
    find_way(maze);
//    int_s_to_char_s(maze);
    return 0;
}











/*
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct maze {
    char **map;
    int **ind;
    int **sol;
    int map_size_rows;
    int map_size_cols;
} maze;

#define true 0
#define false 1

char **str_word_totab(const char *str, char c);

void put_into_map(struct maze *maze, char *folder)
{
    struct stat st;
    int fd = open(folder, O_RDONLY);
    char *buff = NULL;

    maze->map = NULL;
    stat(folder, &st);
    buff = malloc(sizeof(char) * (st.st_size + 1));
    if (read(fd, buff, st.st_size) <= 0)
        return;
    maze->map = str_word_totab(buff, '\n');
}

void set_struct_maze(struct maze *maze)
{
    for (maze->map_size_cols = 0; maze->map[0][maze->map_size_cols]; maze->map_size_cols++);
    for (maze->map_size_rows = 0; maze->map[maze->map_size_rows]; maze->map_size_rows++);
    maze->map_size_rows--;
    maze->ind = malloc(sizeof(int *) * (maze->map_size_rows + 1));
    maze->ind[maze->map_size_rows] = NULL;
    maze->sol = malloc(sizeof(int *) * maze->map_size_rows);

    for (int i = 0; i != maze->map_size_rows; i++) {
        maze->ind[i] = malloc(sizeof(int) * maze->map_size_cols);
        maze->sol[i] = malloc(sizeof(int) * maze->map_size_cols);
        memset(maze->sol[i], 0, maze->map_size_cols);
    }
    for (int i = 0; maze->map[i] != NULL; i++) {
        for (int j = 0; maze->map[i][j]; j++) {
            if (maze->map[i][j] == '*')
                maze->ind[i][j] = 1;
            if (maze->map[i][j] == 'X')
                maze->ind[i][j] = 0;
        }
    }
}

void print_maze(struct maze *maze)
{
    for (int i = 0; maze->map[i]; i++)
        printf("%s\n", maze->map[i]);
}

int check_maze(struct maze *maze, int x, int y)
{
    if (x >= 0 && x < maze->map_size_rows && y >= 0 &&
    y < maze->map_size_cols && maze->ind[x][y] == 1)
        return true;
    return false;
}

int solve_maze_algo(struct maze *maze, int x, int y)
{
    print_maze(maze);
    if (x == (maze->map_size_rows - 1) && (y == maze->map_size_cols - 1)) {
        maze->map[x][y] = 'o';
        return true;
    }
    if (check_maze(maze, x, y) == 0) {
        maze->map[x][y] = 'o';
        if (solve_maze_algo(maze, x + 1, y) == 0)
            return true;
        if (solve_maze_algo(maze, x, y + 1) == 0)
            return true;
        maze->map[x][y] = '*';
        return false;
    }
    return false;
}

int solve_maze(struct maze *maze)
{
    if (solve_maze_algo(maze, 0, 0) == 1)
    {
        printf("Solution doesn't exist");
        return false;
    }

    print_maze(maze);
    return true;
}

int main(int ac, char **av)
{
    struct maze *maze = malloc(sizeof(struct maze));

    put_into_map(maze, av[1]);
    set_struct_maze(maze);
    solve_maze(maze);
    return true;
} */
