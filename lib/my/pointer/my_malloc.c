/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_malloc
*/

#include <stdlib.h>

void *my_malloc(size_t size, size_t unit)
{
    size_t malloc_size = size * unit + unit;
    char *result = NULL;

    if (size < 1 || unit < 1)
        return (NULL);
    if ((result = malloc(malloc_size)) == NULL)
        return (NULL);
    for (size_t i = 0; i < malloc_size; i++)
        result[i] = 0;
    return (result);
}