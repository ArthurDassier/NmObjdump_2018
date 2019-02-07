/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "nmobjdump.h"

void if_cmp(Elf64_Shdr **symtab, Elf64_Shdr **strtab, Elf64_Shdr *shdr, char *str)
{
    if (strcmp(&str[shdr->sh_name], ".symtab") == 0)
        *symtab = (Elf64_Shdr *)shdr;
    if (strcmp(&str[shdr->sh_name], ".strtab") == 0)
        *strtab = (Elf64_Shdr *)shdr;
}

void put_things_in_list(chainlist **list, Elf64_Sym *sym,
Elf64_Shdr *shdr, char *str)
{
    int     adr = 0;
    char    type = 0;
    char    *name = NULL;

    if (sym->st_value != 0)
        adr = sym->st_value;
    type = found_type(*sym, shdr);
    name = str + sym->st_name;
    if (*list == NULL)
        *list = init(adr, type, name);
    else
        insert_end(list, adr, type, name);
}

void printe(chainlist *list)
{
    for(; list->next != NULL; list = list->next) {
        if (list->adress != 0)
            printf("%016x %c %s\n", list->adress, list->type, list->name);
        else
            printf("\t\t %c %s\n", list->type, list->name);
    }
    if (list->adress != 0)
        printf("%016x %c %s\n", list->adress, list->type, list->name);
    else
        printf("\t\t %c %s\n", list->type, list->name);
}

void get_section(void *data)
{
    Elf64_Ehdr      *elf = (Elf64_Ehdr *)(data);
    Elf64_Shdr      *shdr = (Elf64_Shdr *) (data + elf->e_shoff);
    Elf64_Shdr      *symtab = NULL;
    Elf64_Shdr      *strtab = NULL;
    Elf64_Sym       *sym = NULL;
    char            *str = (char *) (data + shdr[elf->e_shstrndx].sh_offset);
    chainlist       *list = NULL;

    for (int i = 0; i < elf->e_shnum; ++i) {
        if (shdr[i].sh_size)
            if_cmp(&symtab, &strtab, &shdr[i], str);
    }
    sym = (Elf64_Sym*) (data + symtab->sh_offset);
    str = (char*) (data + strtab->sh_offset);
    for (size_t i = 0; i < (symtab->sh_size / symtab->sh_entsize); ++i) {
        if (sym[i].st_name != 0 && sym[i].st_info != STT_FILE)
            put_things_in_list(&list, &sym[i], shdr, str);
    }
    list = brain(list);
    printe(list);
}

int open_files(char *filename)
{
    int fd = 0;
    void *data = NULL;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (84);
    data = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
    get_section(data);
    close(fd);
    return (0);
}

int main(int ac , char **av)
{
    if (ac == 1)
        return (open_files("a.out"));
    for(int i = 1; i < ac; ++i) {
        if (open_files(av[1]) == 84)
            return (84);
    }
    return (0);
}