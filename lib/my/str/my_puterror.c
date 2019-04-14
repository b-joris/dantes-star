/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_puterror
*/

#include <unistd.h>

static unsigned int my_strlen(char *str)
{
    unsigned int i = 0;

    for (; str && str[i]; i++);
    return (i);
}

int my_puterror(char *str)
{
    if (str)
        write(2, str, my_strlen(str));
    return (84);
}