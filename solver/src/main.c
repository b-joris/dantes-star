/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** zfqzfdq
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct maze {
    char **map;
    unsigned long **ind;
    unsigned long map_size_rows;
    unsigned long map_size_cols;
} maze;

#define true 0
#define false 1

char **str_word_totab(const char *str, char c);

void put_into_map(struct maze *maze, char *folder)
{
    struct stat st;
    unsigned long fd = open(folder, O_RDONLY);
    char *buff = NULL;

    maze->map = NULL;
    stat(folder, &st);
    buff = malloc(sizeof(char) * (st.st_size + 1));
    if (read(fd, buff, st.st_size) <= 0)
        return;
    maze->map = str_word_totab(buff, '\n');
    free(buff);
}

void set_struct_maze(struct maze *maze)
{
    for (maze->map_size_cols = 0; maze->map[0][maze->map_size_cols]; maze->map_size_cols++);
    for (maze->map_size_rows = 0; maze->map[maze->map_size_rows]; maze->map_size_rows++);
    maze->map_size_rows--;
    maze->ind = malloc(sizeof(unsigned long *) * (maze->map_size_rows + 1));
    maze->ind[maze->map_size_rows] = NULL;

    for (unsigned long i = 0; i != maze->map_size_rows; i++)
        maze->ind[i] = malloc(sizeof(unsigned long) * maze->map_size_cols);
    for (unsigned long i = 0; maze->map[i] != NULL; i++) {
        for (unsigned long j = 0; maze->map[i][j]; j++) {
            if (maze->map[i][j] == '*')
                maze->ind[i][j] = 0;
            if (maze->map[i][j] == 'X')
                maze->ind[i][j] = 1;
        }
    }
}

void print_solution(struct  maze *maze)
{
    for(unsigned long i = 0; i < maze->map_size_rows; i++)
        printf("%s\n", maze->map[i]);
}

unsigned long solvemaze(struct maze *maze, unsigned long r, unsigned long c)
{
    if ((r==maze->map_size_rows - 1) && (c == maze->map_size_cols - 1)) {
        maze->map[r][c] = 'o';
        return false;
    }
    if (r >= 0 && c >= 0 && r < maze->map_size_rows && c < maze->map_size_cols
    && maze->ind[r][c] == 0 && maze->map[r][c] == '*') {
        maze->map[r][c] = 'o';
        if (solvemaze(maze, r + 1, c))
            return false;
        if (solvemaze(maze, r, c + 1))
            return false;
        if (solvemaze(maze, r - 1, c))
            return false;
        if (solvemaze(maze, r, c - 1))
            return false;
        maze->map[r][c] = '*';
    }
    return true;
}

int main(int ac, char **av)
{
    struct maze *maze = malloc(sizeof(struct maze));

    put_into_map(maze, av[1]);
    set_struct_maze(maze);
    if (solvemaze(maze, 0, 0))
        print_solution(maze);
    else
       printf("No solution\n");
    return 0;
}