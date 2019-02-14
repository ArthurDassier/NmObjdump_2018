/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "nmobjdump.h"

int main(int ac , char **av)
{
    if (ac == 1)
        return (open_files("a.out"));
    for (int i = 1; i < ac; ++i) {
        if (open_files(av[1]) == 84)
            return (84);
    }
    return (0);
}