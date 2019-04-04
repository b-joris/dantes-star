/*
** EPITECH PROJECT, 2019
** Lib
** File description:
** my_strcat
*/

#include <stdlib.h>
#include "my_str.h"
#include "my_pointer.h"

char *my_strcat(char *s1, char *s2)
{
    char *new_str = NULL;
    unsigned int len = my_strlen(s1) + my_strlen(s2);
    unsigned int i = 0;

    if (!(new_str = my_malloc(len, sizeof(char))))
        return (NULL);
    for (; s1 && s1[i]; i++)
        new_str[i] = s1[i];
    for (unsigned int j = 0; s2 && s2[j]; i++, j++)
        new_str[i] = s2[j];
    return (new_str);
}