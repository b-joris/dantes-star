/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** astral
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DBL_MAX 1.79769e+308
struct stop {
    double col, row;
    /* array of indexes of routes from this stop to neighbours in array of all routes */
    int * n;
    int n_len;
    double f, g, h;
    int from;
};

struct route {
    /* route has only one direction! */
    int x; /* index of stop in array of all stops of src of this route */
    int y; /* intex of stop in array of all stops od dst of this route */
    double d;
};

typedef struct maze {
    char **map;
    int **ind;
    int map_size_rows;
    int map_size_cols;
} maze;

char **str_word_totab(const char *str, char c);

void put_into_map(struct maze *maze, char *folder)
{
    maze->map = NULL;
    struct stat st;
    int fd = open(folder, O_RDONLY);
    char *buff = NULL;

    stat(folder, &st);
    buff = malloc(sizeof(char) * (st.st_size + 1));
    if (read(fd, buff, st.st_size) <= 0)
        return;
    maze->map = str_word_totab(buff, '\n');
/*     for (int i = 0; maze->map && maze->map[i]; i++) {
        printf("%s\n", maze->map[i]);
    } */

}

void set_struct_maze(struct maze *maze)
{
    for (maze->map_size_cols = 0; maze->map[0][maze->map_size_cols]; maze->map_size_cols++);
    for (maze->map_size_rows = 1; maze->map[maze->map_size_rows]; maze->map_size_rows++);
    maze->ind = malloc(sizeof(int *) * (maze->map_size_rows + 1));
    maze->ind[maze->map_size_rows] = NULL;
    for (int i = 0; i < maze->map_size_rows; i++) {
        maze->ind[i] = malloc(sizeof(int) * maze->map_size_cols);
        memset(maze->ind[i], -1, sizeof(int) * maze->map_size_cols);
    
    for (int i = 0; i != maze->map_size_rows; i++)
        for (int j = 0; j != maze->map_size_cols; j++) {
            if (maze->map[i][j] == '*')
                maze->map[i][j] = 0;
            if (maze->map[i][j] == 'X')
                maze->map[i][j] = 1;
        }
    }
}
int main(int ac, char **av)
{
    struct maze *maze = malloc(sizeof(struct maze));
    put_into_map(maze, av[1]);
    set_struct_maze(maze);

    int i, j, k, l, b, found;
    int p_len = 0;
    int * path = NULL;
    int c_len = 0;
    int * closed = NULL;
    int o_len = 1;
    int * open = (int*)calloc(o_len, sizeof(int));
    double min, tempg;
    int s;
    int e;
    int current;
    int s_len = 0;
    struct stop *stops = NULL;
    int r_len = 0;
    struct route *routes = NULL;
 
    for (i = 1; i < maze->map_size_rows - 1; i++) {
        for (j = 1; j < maze->map_size_cols - 1; j++) {
            if (!maze->map[i][j]) {
                ++s_len;
                stops = (struct stop *)realloc(stops, s_len * sizeof(struct stop));
                int t = s_len - 1;
                stops[t].col = j;
                stops[t].row = i;
                stops[t].from = -1;
                stops[t].g = DBL_MAX;
                stops[t].n_len = 0;
                stops[t].n = NULL;
                maze->ind[i][j] = t;
            }
        }
    }

    s = 0;
    printf("s_len = %i\n", s_len - 1);
    e = s_len - 1;

    for (i = 0; i < s_len; i++) {
        stops[i].h = sqrt(pow(stops[e].row - stops[i].row, 2) + pow(stops[e].col - stops[i].col, 2));
    }

    for (i = 1; i < maze->map_size_rows - 1; i++) {
        for (j = 1; j < maze->map_size_cols - 1; j++) {
            if (maze->ind[i][j] >= 0) {
                for (k = i - 1; k <= i + 1; k++) {
                    for (l = j - 1; l <= j + 1; l++) {
                        if ((k == i) && (l == j)) {
                            continue;
                        }
                        if (maze->ind[k][l] >= 0) {
                            ++r_len;
                            routes = (struct route *)realloc(routes, r_len * sizeof(struct route));
                            int t = r_len - 1;
                            routes[t].x = maze->ind[i][j];
                            routes[t].y = maze->ind[k][l];
                            routes[t].d = sqrt(pow(stops[routes[t].y].row - stops[routes[t].x].row, 2) + pow(stops[routes[t].y].col - stops[routes[t].x].col, 2));
                            ++stops[routes[t].x].n_len;
                            stops[routes[t].x].n = (int *)realloc(stops[routes[t].x].n, stops[routes[t].x].n_len * sizeof(int));
                            stops[routes[t].x].n[stops[routes[t].x].n_len - 1] = t;
                        }
                    }
                }
            }
        }
    }
    open[0] = s;
    stops[s].g = 0;
    stops[s].f = stops[s].g + stops[s].h;
    found = 0;
 
    while (o_len && !found) {
        min = DBL_MAX;
 
        for (i = 0; i < o_len; i++) {
            if (stops[open[i]].f < min) {
                current = open[i];
                min = stops[open[i]].f;
            }
        }
 
        if (current == e) {
            found = 1;
            ++p_len;
            path = (int*)realloc(path, p_len * sizeof(int));
            path[p_len - 1] = current;
            while (stops[current].from >= 0) {
                current = stops[current].from;
                ++p_len;
                path = (int*)realloc(path, p_len * sizeof(int));
                path[p_len - 1] = current;
            }
        }
 
        for (i = 0; i < o_len; i++) {
            if (open[i] == current) {
                if (i != (o_len - 1)) {
                    for (j = i; j < (o_len - 1); j++) {
                        open[j] = open[j + 1];
                    }
                }
                --o_len;
                open = (int*)realloc(open, o_len * sizeof(int));
                break;
            }
        }
        ++c_len;
        closed = (int*)realloc(closed, c_len * sizeof(int));
        closed[c_len - 1] = current;
 
        for (i = 0; i < stops[current].n_len; i++) {
            b = 0;
 
            for (j = 0; j < c_len; j++) {
                if (routes[stops[current].n[i]].y == closed[j]) {
                    b = 1;
                }
            }
 
            if (b) {
                continue;
            }
 
            //tempg = stops[current].g + routes[stops[current].n[i]].d;
 
            b = 1;
 
            if (o_len > 0) {
                for (j = 0; j < o_len; j++) {
                    if (routes[stops[current].n[i]].y == open[j]) {
                        b = 0;
                    }
                }
            }

            if (b || (tempg < stops[routes[stops[current].n[i]].y].g)) { 
                stops[routes[stops[current].n[i]].y].from = current;
                stops[routes[stops[current].n[i]].y].g = tempg;
                stops[routes[stops[current].n[i]].y].f = stops[routes[stops[current].n[i]].y].g + stops[routes[stops[current].n[i]].y].h;

                if (b) {
                    ++o_len;
                    open = (int*)realloc(open, o_len * sizeof(int));
                    open[o_len - 1] = routes[stops[current].n[i]].y;
                }
            }
        }
    }
 
    for (i = 0; i < maze->map_size_rows; i++) {
        for (j = 0; j < maze->map_size_cols; j++) {
            if (maze->map[i][j]) {
                putchar('|');
            } else {
                b = 0;
                for (k = 0; k < p_len; k++) {
                    if (maze->ind[i][j] == path[k]) {
                        ++b;
                    }
                }
                if (b) {
                    putchar('o');
                } else {
                    putchar('.');
                }
            }
        }
        putchar('\n');
    }
 
    if (!found)
        puts("IMPOSSIBLE");

    for (i = 0; i < s_len; ++i) {
        free(stops[i].n);
    }
    free(stops);
    free(routes);
    free(path);
    free(open);
    free(closed);
    return 0;
}