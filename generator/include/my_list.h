/*
** EPITECH PROJECT, 2019
** generator
** File description:
** my_list
*/

#ifndef MY_LIST_H_
#define MY_LIST_H_

typedef struct s_list {
    int x;
    int y;
    struct s_list *next;
} list_t;

list_t *add_node_at_start(list_t *list, int x, int y);
list_t *remove_node_at_start(list_t *list);
void free_list(list_t *list);

#endif /* !MY_LIST_H_ */
