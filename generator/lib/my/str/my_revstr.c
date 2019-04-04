/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_revstr
*/

#include "my_str.h"

void my_revstr(char *str)
{
    unsigned int count = my_strlen(str);
    char c;

    for (unsigned i = 0; i < count / 2; i++) {
        c = str[i];
        str[i] = str[count - 1 - i];
        str[count - 1 - i] = c;
    }
}