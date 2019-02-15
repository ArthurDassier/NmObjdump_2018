/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "nmobjdump.h"

static void if_cmp(Elf64_Shdr **symtab, Elf64_Shdr **strtab,
Elf64_Shdr *shdr, char *str)
{
    if (strcmp(&str[shdr->sh_name], ".symtab") == 0)
        *symtab = (Elf64_Shdr *)shdr;
    if (strcmp(&str[shdr->sh_name], ".strtab") == 0)
        *strtab = (Elf64_Shdr *)shdr;
}

void put_things_in_list(chainlist **list, Elf64_Sym *sym,
Elf64_Shdr *shdr, char *str)
{
    char *name = NULL;
    char type = 0;
    int adr = 0;

    if (sym->st_value != 0)
        adr = sym->st_value;
    type = found_type_six(*sym, shdr);
    name = str + sym->st_name;
    if (*list == NULL)
        *list = init(adr, type, name);
    else
        insert_end(list, adr, type, name);
}

int get_section(void *data, Elf64_Shdr *symtab,
Elf64_Shdr *strtab, Elf64_Sym *sym)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)(data);
    Elf64_Shdr *shdr = (Elf64_Shdr *) (data + elf->e_shoff);
    chainlist *list = NULL;
    char *str = NULL;

    check_elf(elf, shdr, data);
    str = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    getter(str, 1);
    for (int i = 0; i < elf->e_shnum; ++i)
        if (shdr[i].sh_size)
            if_cmp(&symtab, &strtab, &shdr[i], str);
    if (symtab == NULL)
        return (1);
    sym = (Elf64_Sym*) (data + symtab->sh_offset);
    str = (char*) (data + strtab->sh_offset);
    if (sym == NULL || str == NULL)
        exit(84);
    for (size_t i = 0; i < (symtab->sh_size / symtab->sh_entsize); ++i)
        if (sym[i].st_name != 0 && sym[i].st_info != STT_FILE)
            put_things_in_list(&list, &sym[i], shdr, str);
    list = brain(list);
    print_me_that(list);
    return (0);
}

int open_files(char *binary_name, char *filename)
{
    void *data = NULL;
    int fd = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (84);
    data = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
    if (get_section(data, NULL, NULL, NULL))
        printf("%s: %s: no symbols\n", binary_name, filename);
    close(fd);
    return (0);
}