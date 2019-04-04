/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_strdup
*/

#include "my_pointer.h"
#include "my_str.h"

char *my_strdup(char *str)
{
    char *new_str = my_malloc(my_strlen(str), sizeof(char));

    if (!new_str)
        return (NULL);
    for (unsigned int i = 0; str[i]; i++)
        new_str[i] = str[i];
    return (new_str);
}