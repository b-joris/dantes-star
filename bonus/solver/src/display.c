/*
** EPITECH PROJECT, 2019
** bonus
** File description:
** display
*/

#include <unistd.h>
#include <ncurses.h>
#include "solver.h"

void display_maze(maze_t *maze)
{
    int width = COLS / 2 - maze->width / 2;
    int height = LINES / 2 - maze->height / 2;

    for (int y = 0; y < maze->height - 1; y++) {
        for (int x = 0; x < maze->width - 1; x++) {
            if (maze->grid[POS(y, x, maze->width)] == PATH)
                attron(COLOR_PAIR(PATH));
            if (maze->grid[POS(y, x, maze->width)] == WALL)
                attron(COLOR_PAIR(WALL));
            if (maze->grid[POS(y, x, maze->width)] == PASS)
                attron(COLOR_PAIR(PASS));
            if (maze->grid[POS(y, x, maze->width)] == PASSED)
                attron(COLOR_PAIR(PASSED));
            mvprintw(height + y, width + x, "%c", maze->grid[POS(y, x, maze->width)]);
        }
    }
    refresh();
    usleep(80000);
}