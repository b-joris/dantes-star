/*
** EPITECH PROJECT, 2019
** bonus
** File description:
** display
*/

#include <ncurses.h>
#include <unistd.h>
#include "generator.h"

void display_maze(maze_t *maze)
{
    int width = COLS / 2 - maze->width / 2;
    int height = LINES / 2 - maze->height / 2;

    for (int y = 0; y < maze->height - 1; y++) {
        for (int x = 0; x < maze->width - 1; x++) {
            if (maze->grid[y][x] == '*')
                attron(COLOR_PAIR(PATH));
            else
                attron(COLOR_PAIR(WALL));
            mvprintw(height + y, width + x, "%c", maze->grid[y][x]);
        }
    }
    refresh();
    usleep(125000);
}