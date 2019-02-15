/*
** EPITECH PROJECT, 2019
** print.c
** File description:
** print
*/

#include "nmobjdump.h"

void print_me_that(chainlist *list)
{
    static int a = 0;

    for (; list->next != NULL; list = list->next) {
        ++a;
        if (list->type != 'U' && list->type != 'w')
            printf("%016x %c %s\n", list->adress, list->type, list->name);
        else
            printf("\t\t %c %s\n", list->type, list->name);
    }
    if (list->type != 'U' && list->type != 'w')
        printf("%016x %c %s\n", list->adress, list->type, list->name);
    else
        printf("\t\t %c %s\n", list->type, list->name);
    printf("%d : \n", a);
}
