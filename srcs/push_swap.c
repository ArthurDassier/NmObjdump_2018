/*
** EPITECH PROJECT, 2017
** push_swap.c
** File description:
** pushwap
*/

#include "nmobjdump.h"

chainlist *brain(chainlist *liste)
{
    chainlist   *list_a = liste;
    chainlist   *list_b = NULL;

    while (is_sup(list_a) == 1) {
        if (is_sup(list_a) == 1)
            ra(&list_a);
        if (recup(list_a) == 1)
            pb(&list_a, &list_b);
    }
    while (list_b != NULL)
        pa(&list_b, &list_a);
    return (list_a);
}
