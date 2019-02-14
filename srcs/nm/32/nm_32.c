/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "nmobjdump.h"

void if_cmp32(Elf32_Shdr **symtab, Elf32_Shdr **strtab, Elf32_Shdr *shdr, char *str)
{
    if (strcmp(&str[shdr->sh_name], ".symtab") == 0)
        *symtab = (Elf32_Shdr *)shdr;
    if (strcmp(&str[shdr->sh_name], ".strtab") == 0)
        *strtab = (Elf32_Shdr *)shdr;
}

void put_things_in_list32(chainlist **list, Elf32_Sym *sym,
Elf32_Shdr *shdr, char *str)
{
    int     adr = 0;
    char    type = 0;
    char    *name = NULL;

    if (sym->st_value != 0)
        adr = sym->st_value;
    type = found_type32(*sym, shdr);
    name = str + sym->st_name;
    if (*list == NULL)
        *list = init(adr, type, name);
    else
        insert_end(list, adr, type, name);
}

void get_section32(void *data)
{
    Elf32_Ehdr      *elf = (Elf32_Ehdr *)(data);
    Elf32_Shdr      *shdr = (Elf32_Shdr *) (data + elf->e_shoff);
    Elf32_Shdr      *symtab = NULL;
    Elf32_Shdr      *strtab = NULL;
    Elf32_Sym       *sym = NULL;
    char            *str = NULL;
    chainlist       *list = NULL;

    if (elf == NULL || shdr == NULL || data == NULL)
        exit(84);
    str = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    for (int i = 0; i < elf->e_shnum; ++i) {
        if (shdr[i].sh_size)
            if_cmp32(&symtab, &strtab, &shdr[i], str);
    }
    sym = (Elf32_Sym*) (data + symtab->sh_offset);
    str = (char*) (data + strtab->sh_offset);
    if (sym == NULL || str == NULL)
        exit(84);
    for (size_t i = 0; i < (symtab->sh_size / symtab->sh_entsize); ++i) {
        if (sym[i].st_name != 0 && sym[i].st_info != STT_FILE)
            put_things_in_list32(&list, &sym[i], shdr, str);
    }
    list = brain(list);
    print_me_that(list);
}
