/*
** EPITECH PROJECT, 2019
** push_swap.c
** File description:
** pushwap
*/

#include "nmobjdump.h"

void sort_and_print(chainlist *liste)
{
    chainlist *list_a = liste;
    chainlist *list_b = NULL;

    while (is_sup(list_a) == 1) {
        if (is_sup(list_a) == 1)
            ra(&list_a);
        if (recup(list_a) == 1)
            pb(&list_a, &list_b);
    }
    while (list_b != NULL)
        pa(&list_b, &list_a);
    print_me_that(list_a);
}
