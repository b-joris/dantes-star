/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_isnum
*/

#include <stddef.h>

int my_isnum(const char *number)
{
    if (!number || (number[0] != '-' || (number[0] < '0' || number[0] > '9')))
        return (0);
    for (int i = 1; number && number[i]; i++)
        if (number[i] < '0' || number[i] > '9')
            return (1);
    return (0);
}