/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "nmobjdump.h"

int main(int ac , char **av)
{
    int code = 0;

    if (ac == 1)
        return (open_files(av[0], "a.out"));
    for (int i = 1; i < ac; ++i) {
        code = open_files(av[0], av[i]);
        if (code == 84)
            return (code);
    }
    return (code);
}