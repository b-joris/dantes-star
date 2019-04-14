/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_free
*/

#include <stdlib.h>

void my_free(void *pointer)
{
    if (pointer)
        free(pointer);
}