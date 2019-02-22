/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "nmobjdump.h"

static void cmp_three(Elf32_Shdr **symtab, Elf32_Shdr **strtab,
Elf32_Shdr *shdr, char *str)
{
    if (strcmp(&str[shdr->sh_name], ".symtab") == 0)
        *symtab = (Elf32_Shdr *)shdr;
    if (strcmp(&str[shdr->sh_name], ".strtab") == 0)
        *strtab = (Elf32_Shdr *)shdr;
}

void put_things_in_list_three(chainlist **list, Elf32_Sym *sym,
Elf32_Shdr *shdr, char *str)
{
    char type = 0;
    char *name = NULL;
    int adr = 0;

    if (sym->st_value != 0)
        adr = sym->st_value;
    type = found_type_three(*sym, shdr);
    name = str + sym->st_name;
    if (*list == NULL)
        *list = init(adr, type, name);
    else
        insert_end(list, adr, type, name);
}

int get_section_three(void *data, Elf32_Shdr *symtab,
Elf32_Shdr *strtab, Elf32_Sym *sym)
{
    Elf32_Ehdr *elf = (Elf32_Ehdr *)(data);
    Elf32_Shdr *shdr = (Elf32_Shdr *) (data + elf->e_shoff);
    chainlist *list = NULL;
    char *str = (char *)(data + shdr[elf->e_shstrndx].sh_offset);

    getter(str, 1);
    for (int i = 0; i < elf->e_shnum; ++i)
        if (shdr[i].sh_size)
            cmp_three(&symtab, &strtab, &shdr[i], str);
    if (symtab == NULL)
        return (1);
    sym = (Elf32_Sym*) (data + symtab->sh_offset);
    str = (char*) (data + strtab->sh_offset);
    if (sym == NULL || str == NULL)
        return (84);
    for (size_t i = 0; i < (symtab->sh_size / symtab->sh_entsize); ++i)
        if (sym[i].st_name != 0 && sym[i].st_info != STT_FILE)
            put_things_in_list_three(&list, &sym[i], shdr, str);
    sort_and_print(list);
    return (2);
}
