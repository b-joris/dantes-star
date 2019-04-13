/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_strlen
*/

#include <stdlib.h>

unsigned int my_strlen(char *str)
{
    unsigned int size = 0;

    for (; str && str[size]; size++);
    return (size);
}