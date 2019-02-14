/*
** EPITECH PROJECT, 2019
** actions2.c
** File description:
** actions
*/

#include <ctype.h>
#include "nmobjdump.h"

void verify_elf(Elf64_Ehdr *elf, Elf64_Shdr *shdr, void *data)
{
    if (elf == NULL || shdr == NULL || data == NULL)
        exit(84);
    if (elf->e_ident[0] != ELFMAG0 || elf->e_ident[1] != ELFMAG1
    || elf->e_ident[2] != ELFMAG2 || elf->e_ident[3] != ELFMAG3)
        exit(84);
    if (elf->e_ident[4] == 1) {
        get_section_three(data, NULL, NULL, NULL);
        exit(0);
    }
}

int my_strcmp(char const *s1, char const *s2, int i, int j)
{
    while ((s1[i] == '_' || s1[i] == '.') && s1[i])
        ++i;
    while ((s2[j] == '_' || s2[j] == '.') && s2[j])
        ++j;
    while (tolower(s1[i]) == tolower(s2[j]) && s1[i] && s2[j]) {
        ++j;
        ++i;
        while (!(isalnum(s1[i])) && s1[i])
            ++i;
        while (!(isalnum(s2[j])) && s2[j])
            ++j;
    }
    if ((s1[i] == '\0' && s2[j] == '\0')) {
        if (s1[0] == '_')
            return (1);
        return (0);
    } else if (tolower(s1[i]) > tolower(s2[j]))
        return (1);
    else
        return (0);
}

void pb(chainlist **list_out, chainlist **list_in)
{
    chainlist *tmp = (*list_out);
    chainlist *tmp2 = (*list_in);

    (*list_out) = (*list_out)->next;
    (*list_in) = tmp;
    (*list_in)->next = tmp2;
}