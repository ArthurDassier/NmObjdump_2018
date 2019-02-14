/*
** EPITECH PROJECT, 2019
** actions2.c
** File description:
** actions
*/

#include "nmobjdump.h"

void pb(chainlist **list_out, chainlist **list_in)
{
    chainlist *tmp = (*list_out);
    chainlist *tmp2 = (*list_in);

    (*list_out) = (*list_out)->next;
    (*list_in) = tmp;
    (*list_in)->next = tmp2;
}
