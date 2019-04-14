/*
** EPITECH PROJECT, 2019
** CPE_dante_2018
** File description:
** map
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

char *load_map(char *path)
{
    char *map = NULL;
    struct stat st;
    int fd = open(path, O_RDONLY);

    if (fd <= 0)
        return (NULL);
    stat(path, &st);
    map = malloc(sizeof(char) * (st.st_size + 1));
    if (!map) {
        close(fd);
        return (NULL);
    }
    if (read(fd, map, st.st_size) <= 0) {
        close(fd);
        return (NULL);
    }
    close(fd);
    return (map);
}

int count_height(char *map)
{
    int height = 0;

    for (int i = 0; map && map[i]; i++)
        if (map[i] == '\n')
            ++height;
    if (map[(strlen(map) )- 1] != '\n')
        ++height;
    return (height);
}

int count_width(char *map)
{
    int width = 0;

    for (; (map && map[width]) && map[width] != '\n'; width++);
    return (width);
}