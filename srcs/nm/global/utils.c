/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils
*/

#include <ctype.h>
#include "nmobjdump.h"

char *getter(char *str, int value)
{
    static char *tamer;

    if (value == 1)
        tamer = str;
    return (tamer);
}

int check_elf(Elf64_Ehdr *elf, void *data, char *binary_name, char *filename)
{
    if (data == NULL)
        return (84);
    if (elf == NULL || data == (void *) -1) {
        fprintf(stderr, "%s: Warning: '%s' is a directory\n",
        binary_name, filename);
        return (-1);
    }
    if (elf->e_ident[0] != ELFMAG0 || elf->e_ident[1] != ELFMAG1
    || elf->e_ident[2] != ELFMAG2 || elf->e_ident[3] != ELFMAG3) {
        fprintf(stderr, "%s: %s: File format not recognized\n",
        binary_name, filename);
        return (-1);
    }
    if (elf->e_ident[4] == 1)
        return (get_section_three(data, NULL, NULL, NULL));
    return (0);
}

static int my_count(char const *str, int i)
{
    while ((str[i] == '_' || str[i] == '.') && str[i])
        ++i;
    return (i);
}

static int my_count_alpha(char const *str, int i)
{
    while (!(isalnum(str[i])) && str[i])
        ++i;
    return (i);
}

int my_strcmp(char const *s1, char const *s2, int i, int j)
{
    i = my_count(s1, i);
    j = my_count(s2, j);
    while (tolower(s1[i]) == tolower(s2[j]) && s1[i] && s2[j]) {
        ++j;
        ++i;
        i = my_count_alpha(s1, i);
        j = my_count_alpha(s2, j);
    }
    if ((s1[i] == '\0' && s2[j] == '\0')) {
        if (s1[0] == '_')
            return (1);
        return (0);
    }
    if (tolower(s1[i]) > tolower(s2[j]))
        return (1);
    return (0);
}