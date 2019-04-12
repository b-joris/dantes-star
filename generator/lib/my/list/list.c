/*
** EPITECH PROJECT, 2019
** generator
** File description:
** list
*/

#include <stdlib.h>
#include "my_list.h"

list_t *add_node_at_start(list_t *list, int x, int y)
{
    list_t *node = malloc(sizeof(list_t));

    if (!node)
        return (NULL);
    node->x = x;
    node->y = y;
    if (!list)
        node->next = NULL;
    else
        node->next = list;
    return (node);
}

list_t *remove_node_at_start(list_t *list)
{
    list_t *temp = NULL;

    if (!list)
        return (NULL);
    temp = list->next;
    free(list);
    return (temp);
}

void free_list(list_t *list)
{
    list_t *temp = NULL;

    while (list) {
        temp = list;
        list = list->next;
        free(temp);
    }
}