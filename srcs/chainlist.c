/*
** EPITECH PROJECT, 2019
** chainlist.c
** File description:
** chainlist
*/

#include "nmobjdump.h"

chainlist *init(int adress, char type, char *name)
{
    chainlist   *element = malloc(sizeof(*element));

    element->adress = adress;
    element->type = type;
    element->name = name;
    element->next = NULL;
    return (element);
}

void insert_begin(chainlist **first_elem, int adress, char type, char *name)
{
    chainlist   *new_elem = malloc(sizeof(chainlist));

    if (new_elem == NULL)
        return;
    new_elem->adress = adress;
    new_elem->type = type;
    new_elem->name = name;
    new_elem->next = *first_elem;
    (*first_elem) = new_elem;
}

void insert_end(chainlist **first_elem, int adress, char type, char *name)
{
    chainlist   *new_elem = malloc(sizeof(chainlist));
    chainlist   *actual = (*first_elem);

    if (new_elem == NULL)
        return;
    new_elem->adress = adress;
    new_elem->type = type;
    new_elem->name = name;
    new_elem->next = NULL;
    while (actual->next != NULL) {
        actual = actual->next;
    }
    actual->next = new_elem;
}
