/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_putstr
*/

#include <unistd.h>
#include "my_str.h"

void my_putstr(char *str)
{
    if (str)
        write(1, str, my_strlen(str));
}