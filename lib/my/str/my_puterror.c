/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_puterror
*/

#include <unistd.h>
#include "my_str.h"

int my_puterror(char *str)
{
    if (str)
        write(2, str, my_strlen(str));
    return (84);
}