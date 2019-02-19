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

int get_section(void *data, Elf64_Ehdr *elf,
Elf64_Shdr *strtab, Elf64_Sym *sym)
{
    Elf64_Shdr *shdr = (Elf64_Shdr *) (data + elf->e_shoff);
    Elf64_Shdr *symtab = NULL;
    chainlist *list = NULL;
    char *str = (char *)(data + shdr[elf->e_shstrndx].sh_offset);

    getter(str, 1);
    for (int i = 0; i < elf->e_shnum; ++i)
        if (shdr[i].sh_size)
            if_cmp(&symtab, &strtab, &shdr[i], str);
    if (symtab == NULL)
        return (1);
    sym = (Elf64_Sym*) (data + symtab->sh_offset);
    str = (char*) (data + strtab->sh_offset);
    if (sym == NULL || str == NULL)
        return (84);
    for (size_t i = 0; i < (symtab->sh_size / symtab->sh_entsize); ++i)
        if (sym[i].st_name != 0 && sym[i].st_info != STT_FILE)
            put_things_in_list(&list, &sym[i], shdr, str);
    sort_and_print(list);
    return (0);
}

int check_format(void *data)
{
    int code = 0;
    Elf64_Ehdr *elf = (Elf64_Ehdr *)(data);

    code = check_elf(elf, data);
    if (code == 1)
        return (1);
    if (code == 2)
        return (0);
    if (code == -1)
        return (-1);
    if (code == 84)
        return (84);
    return (get_section(data, elf, NULL, NULL));
}

int open_files(char *binary_name, char *filename)
{
    void *data = NULL;
    int fd = open(filename, O_RDONLY);
    int code = 0;

    if (fd == -1) {
        fprintf(stderr, "%s: '%s': No such file\n", binary_name, filename);
        return (1);
    }
    data = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
    code = check_format(data);
    close(fd);
    if (code == 1) {
        fprintf(stderr, "%s: %s: no symbols\n", binary_name, filename);
        return (1);
    }
    if (code == 84)
        return (84);
    if (code == -1)
        return (1);
    return (0);
}