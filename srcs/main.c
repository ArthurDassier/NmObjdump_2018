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
        *symtab = (Elf64_Shdr *) shdr;
    if (strcmp(&str[shdr->sh_name], ".strtab") == 0)
        *strtab = (Elf64_Shdr *) shdr;
}

void print_things(Elf64_Sym *sym, Elf64_Shdr *shdr, char *str, size_t i)
{
    if (sym[i].st_value != 0)
        printf("%016lx ", sym[i].st_value);
    else
        printf("\t\t ");
    printf("%c %s\n", print_type(sym[i], shdr), str + sym[i].st_name);
}

void get_section(void *data)
{
    Elf64_Ehdr      *elf = (Elf64_Ehdr *)(data);
    Elf64_Shdr      *shdr = (Elf64_Shdr *) (data + elf->e_shoff);
    Elf64_Shdr      *symtab = NULL;
    Elf64_Shdr      *strtab = NULL;
    Elf64_Sym       *sym = NULL;
    char            *str = (char *) (data + shdr[elf->e_shstrndx].sh_offset);

    for (int i = 0; i < elf->e_shnum; ++i) {
        if (shdr[i].sh_size)
            if_cmp(&symtab, &strtab, &shdr[i], str);
    }
    sym = (Elf64_Sym*) (data + symtab->sh_offset);
    str = (char*) (data + strtab->sh_offset);
    for (size_t i = 0; i < (symtab->sh_size / symtab->sh_entsize); ++i) {
        if (sym[i].st_name != 0 && sym[i].st_info != STT_FILE)
            print_things(sym, shdr, str, i);
    }
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