/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** str_word_totab
*/

#include <stdlib.h>

int count_words(const char *str, char c)
{
    int count = 1;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            count++;
    return (count);
}

char **str_word_totab(const char *str, char c)
{
    int count = count_words(str, c);
    char ** array = malloc(sizeof(char *) * (count + 1));
    int x = 0;
    int len = 0;

    array[count] = 0;
    for (int i = 0; i != count; i++, x++) {
        for (; str[x] != c && str[x] != '\0'; x++, len++);
        array[i] = malloc(sizeof(char) * (len));
        for (int j = 0; j < len; j++)
            array[i][j] = '0';
        array[i][len] = '\0';
        len = 0;
    }
    x = 0;
    for (int i = 0; i != count; i++, x++)
        for (int j = 0; array[i][j] != '\0'; j++, x++)
            array[i][j] = str[x];
    return (array);
}
