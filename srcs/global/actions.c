/*
** EPITECH PROJECT, 2019
** actions.c
** File description:
** actions
*/

#include "nmobjdump.h"

int is_sup(chainlist *first_elem)
{
    chainlist   *actual = first_elem;

    while (actual->next != NULL) {
        if (my_strcmp(actual->name, actual->next->name, 0, 0))
            return (1);
        actual = actual->next;
    }
    return (0);
}

void sa(chainlist **list)
{
    chainlist   *tmp = (*list);
    chainlist   *tmp2 = (*list)->next;

    tmp->next = tmp2->next;
    tmp2->next = tmp;
    *list = tmp2;
}

void ra(chainlist **list)
{
    chainlist   *tmp = *list;

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = (*list);
    (*list) = (*list)->next;
    tmp = tmp->next;
    tmp->next = NULL;
}

void pa(chainlist **list_out, chainlist **list_in)
{
    chainlist   *tmp = (*list_out);
    chainlist   *tmp2 = (*list_in);

    (*list_out) = (*list_out)->next;
    (*list_in) = tmp;
    (*list_in)->next =  tmp2;
}

int recup(chainlist *first_elem)
{
    chainlist   *tmp = first_elem;
    chainlist   *tmp2 = first_elem;

    while (tmp->next != NULL) {
        if (my_strcmp(tmp2->name, tmp->next->name, 0, 0))
            return (0);
        tmp = tmp->next;
    }
    return (1);
}
