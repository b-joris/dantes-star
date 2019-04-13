/*
** EPITECH PROJECT, 2019
** Visual Studio Live Share (Workspace)
** File description:
** my_strlen
*/

#include <stdlib.h>

int my_strlen(char *str)
{
    int i = 0;

    for (; str != NULL && str[i] != '\0'; i++);
    return (i);
}